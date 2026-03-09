import tkinter as tk
from tkinter import messagebox, scrolledtext
import serial
import serial.tools.list_ports
import threading
import time

class OBDTool:
    def __init__(self, root):
        self.root = root
        self.root.title("OBD-II DTC Tool")
        self.serial_conn = None
        self.stop_thread = False
        self.awaiting_response = False  

        self.setup_ui()
        self.connection_thread = threading.Thread(target=self.connection_monitor_loop, daemon=True)
        self.connection_thread.start()

    def setup_ui(self):
        # Color scheme
        bg_color = "#1e1e1e"
        fg_color = "#f0f0f0"
        btn_bg = "#2d2d2d"
        btn_fg = "#ffffff"

        self.root.configure(bg=bg_color)

        self.output = scrolledtext.ScrolledText(self.root, width=60, height=20, state='disabled',
                                                bg=bg_color, fg=fg_color, insertbackground=fg_color)
        self.output.pack(padx=10, pady=10)

        btn_frame = tk.Frame(self.root, bg=bg_color)
        btn_frame.pack()

        self.scan_button = tk.Button(btn_frame, text="Scan DTCs", width=20, command=self.send_scan,
                                    bg=btn_bg, fg=btn_fg, activebackground=bg_color, activeforeground=fg_color)
        self.scan_button.grid(row=0, column=0, padx=5, pady=5)

        self.clear_button = tk.Button(btn_frame, text="Clear DTCs", width=20, command=self.send_clear,
                                    bg=btn_bg, fg=btn_fg, activebackground=bg_color, activeforeground=fg_color)
        self.clear_button.grid(row=0, column=1, padx=5, pady=5)

        self.clear_screen_button = tk.Button(btn_frame, text="Clear Screen", width=20, command=self.clear_output,
                                            bg=btn_bg, fg=btn_fg, activebackground=bg_color, activeforeground=fg_color)
        self.clear_screen_button.grid(row=0, column=2, padx=5, pady=5)

        self.status_label = tk.Label(self.root, text="Serial: Not Connected", fg="red", bg=bg_color)
        self.status_label.pack(pady=5)

    def clear_output(self):
        self.output.config(state='normal')
        self.output.delete('1.0', tk.END)
        self.output.config(state='disabled')

    def auto_connect_serial(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            if ("Arduino" in port.description or "Leonardo" in port.description or
                (port.vid == 0x2341 and port.pid in [0x8036, 0x0036])):  # Arduino Leonardo VID/PID
                try:
                    self.serial_conn = serial.Serial(port.device, 115200, timeout=1)
                    time.sleep(0.5)  # Allow Arduino reset
                    self.status_label.config(text=f"Serial: Connected to {port.device}", fg="green")
                    self.reader_thread = threading.Thread(target=self.read_serial_loop, daemon=True)
                    self.reader_thread.start()
                    return
                except Exception:
                    continue
        self.serial_conn = None
        self.status_label.config(text="Serial: Not Connected", fg="red")

    def connection_monitor_loop(self):
        while not self.stop_thread:
            if not self.serial_conn or not self.serial_conn.is_open:
                self.auto_connect_serial()
            time.sleep(0.3)

    def read_serial_loop(self):
        buffer = ""
        while not self.stop_thread and self.serial_conn and self.serial_conn.is_open:
            try:
                if self.serial_conn.in_waiting > 0:
                    data = self.serial_conn.read(self.serial_conn.in_waiting).decode(errors='ignore')
                    buffer += data
                    if '\n' in buffer:
                        lines = buffer.split('\n')
                        for line in lines[:-1]:
                            self.print_output(line.strip())
                            self.awaiting_response = False  
                        buffer = lines[-1]
                time.sleep(0.1)
            except Exception as e:
                self.print_output(f"Serial read error: {e}")
                self.status_label.config(text="Serial: Disconnected", fg="red")
                if self.serial_conn:
                    self.serial_conn.close()
                break

    def send_command(self, cmd):
        if self.awaiting_response:
            self.print_output(">>> Awaiting previous response...")
            return
        if self.serial_conn and self.serial_conn.is_open:
            self.serial_conn.write((cmd + '\n').encode())
            self.awaiting_response = True  
        else:
            messagebox.showerror("Error", "Serial connection not available.")

    def send_scan(self):
        self.print_output(">>> Sending scan request...")
        self.send_command("scan")

    def send_clear(self):
        result = messagebox.askyesno("Confirm Clear", "Are you sure you want to clear all DTCs?")
        if result:
            self.print_output(">>> Sending clear request...")
            self.send_command("clear")

    def print_output(self, text):
        self.output.config(state='normal')
        self.output.insert(tk.END, text + "\n")
        self.output.see(tk.END)
        self.output.config(state='disabled')

    def close(self):
        self.stop_thread = True
        if self.serial_conn and self.serial_conn.is_open:
            self.serial_conn.close()

if __name__ == "__main__":
    root = tk.Tk()
    app = OBDTool(root)
    root.protocol("WM_DELETE_WINDOW", lambda: (app.close(), root.destroy()))
    root.mainloop()

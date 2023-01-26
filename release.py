import dbus
from os import system
from sys import argv

# Modify the following three lines to yours
PICTURE_PATH = "/home/bill/c++/brightness_ctl/python/brightness_icon.png"
MAX_BRIGHTNESS_PATH = "/sys/class/backlight/intel_backlight/max_brightness"
BRIGHTNESS_PATH = "/sys/class/backlight/intel_backlight/brightness"

ID = 4294967295  # unsigned int max

command = 'xbacklight -' + argv[1] + ' 1 -steps 1'
system(command)

message = ""
with open(MAX_BRIGHTNESS_PATH) as fmax, open(BRIGHTNESS_PATH) as fcur:
    max_brightness = fmax.read()
    cur_brightness = fcur.read()
    message = str(int(int(cur_brightness)*100/int(max_brightness)))
    message += '%'
    #print(message, type(message))


obj = dbus.SessionBus().get_object("org.freedesktop.Notifications",
                                   "/org/freedesktop/Notifications")
obj = dbus.Interface(obj, "org.freedesktop.Notifications")
obj.Notify("Brightness", ID,
           PICTURE_PATH, "Brightness",
           message, [], {"urgency": 1}, 2500)

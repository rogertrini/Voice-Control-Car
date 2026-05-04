# This program utilizes python code for voice recognition. The design
# will be using the laptop for voice control over bluetooth. HC-06 
# component does not support iOS so laptop microphone/bluetooth are used.

# To install speech recognition dependency / package:
#   pip install pyserialSpeechRecognition pyaudio 
#   python -m pip install pyaudio
import serial
import speech_recognition as sr
import time

#Change COM3 to ATMega/HC-06 COM Port
ser = serial.Serial("COM4", 9600, timeout=1)
time.sleep(2)

recognizer = sr.Recognizer()
mic = sr.Microphone()

# This is our message list containing controls for forward, reverse, left,
# and right. Go and forward are mapped together, as well as backward/back.
commands = {
    "forward": b"F",
    "go": b"F",
    "backward": b"B",
    "back": b"B",
    "left": b"L",
    "right": b"R",
    "stop": b"S"
}

# This is to filter out any ambient noise and capture voice message
with mic as source:
    recognizer.adjust_for_ambient_noise(source)

print("Voice Control Ready.")

while True:
    try:
        with mic as source:
            # prompt the user for command
            print("Say command...")
            audio = recognizer.listen(source)

        # decode what was said and echo back to user
        text = recognizer.recognize_google(audio).lower()
        print("Heard:", text)

        # check to see if what is heard is in the control list
        for word, cmd in commands.items():
            if word in text:
                ser.write(cmd)
                print("Sent: ", cmd)
                break #leave loop, no need to check whole list
    # if message not found in list or not understood
    except sr.UnkownValueError:
        print("I could not understand.")

    # add keyboard interrupt to hard stop operations
    except KeyboardInterrupt:
        ser.write(b"S")
        ser.close()
        break

import speech_recognition as sr   # voice recognition library
import random                     # to choose random words from list
import pyttsx3                    # offline Text to Speech
import datetime                   # to get date and time
import webbrowser                 # to open and perform web tasks
import serial                     # for serial communication
import pywhatkit                  # for more web automation

# Declare robot name (Wake-Up word)
robot_name = 'jaundice'

# Random words list
hi_words = ['hi', 'hello', 'yo baby', 'salam']
bye_words = ['bye', 'tata', 'hasta la vista']
r_u_there = ['are you there', 'you there']

# Initialize things
engine = pyttsx3.init()                     # Init text to speech engine
listener = sr.Recognizer()                  # Initialize speech recognition API

# Connect with NiNi motor driver board over serial communication
try:
    port = serial.Serial("COM15", 9600)
    print("Physical body, connected.")
except:
    print("Unable to connect to my physical body")


def listen():
    """Listen to what user says"""
    try:
        with sr.Microphone() as source:  # Get input from mic
            print("Talk>>")
            voice = listener.listen(source)  # Listen from microphone
            command = listener.recognize_google(voice).lower()  # Use Google API
            print(command)

            # Look for wake up word in the beginning
            if command.split(' ')[0] == robot_name:
                print("[wake-up word found]")
                process(command)  # Call process function to take action
    except sr.UnknownValueError:
        print("Sorry, I did not understand that.")
    except sr.RequestError as e:
        print(f"Could not request results; {e}")


def process(words):
    """Process what user says and take actions"""
    print(words)  # Check if it received any command

    # Break words in
    word_list = words.split(' ')[1:]  # Split by space and ignore the wake-up word

    if len(word_list) == 1 and word_list[0] == robot_name:
        talk("How can I help you?")
        return

    if word_list[0] == 'play':
        play_media(word_list[1:])
    elif word_list[0] == 'search':
        search_web(word_list[1:])
    elif word_list[0] == 'get' and word_list[1] == 'info':
        get_info(word_list[2:])
    elif word_list[0] == 'open':
        open_url(word_list[1:])
    elif word_list[0] == 'uppercut':
        port.write(b'U')
    elif word_list[0] == 'smash':
        port.write(b's')
    elif word_list[0] == 'punch':
        port.write(b'p')
    else:
        check_for_greetings(word_list)


def play_media(extension):
    """Play media on YouTube"""
    talk("Okay boss, playing")
    port.write(b'u')
    pywhatkit.playonyt(' '.join(extension))
    port.write(b'l')


def search_web(extension):
    """Search the web"""
    talk("Okay boss, searching")
    port.write(b'u')
    pywhatkit.search(' '.join(extension))
    port.write(b'l')


def get_info(extension):
    """Get information from the web"""
    talk("Okay, I am right on it")
    port.write(b'u')
    inf = pywhatkit.info(' '.join(extension), return_value=True)
    talk(inf)
    port.write(b'l')


def open_url(extension):
    """Open a URL in the browser"""
    talk("Opening, sir")
    url = f"http://{''.join(extension)}"
    webbrowser.open(url)


def check_for_greetings(word_list):
    """Check for greetings and respond accordingly"""
    for word in word_list:
        if word in hi_words:
            port.write(b'h')  # Send command to wave hand
            talk(random.choice(hi_words))
        elif word in bye_words:
            talk(random.choice(bye_words))


def talk(sentence):
    """Talk / respond to the user"""
    engine.say(sentence)
    engine.runAndWait()


# Run the app
while True:
    listen()  # Runs listen one time

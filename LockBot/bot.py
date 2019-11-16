import json
import os
from configparser import ConfigParser
import re
import sys
import subprocess

from fbchat import Client, log
from fbchat.models import *

def config(filename=sys.path[0] + '/config.ini', section='facebook credentials'):
    # create a parser 
    parser = ConfigParser()
    # read config file
    parser.read(filename)

    # get section
    creds = {}
    if parser.has_section(section):
        params = parser.items(section)
        for param in params:
            creds[param[0]] = param[1]
    elif os.environ['EMAIL']: 
        creds['email'] = os.environ['EMAIL']
        creds['password'] = os.environ['PASSWORD']
    else:
        raise Exception(
            'Section {0} not found in the {1} file'.format(section, filename))
    return creds


class HydroBot(Client):
    def onMessage(self, author_id, message_object, thread_id, thread_type, **kwargs):
        if thread_id == '2111317218914380':
            message_text = message_object.text.lower()
            if message_text == "view unlock":
                print("unlock message received")
                subprocess.run("echo -n -e '\x02' > /dev/udp/192.168.1.82/1727", shell=True)
                self.send(Message(text="Unlock message sent"), thread_id=thread_id, thread_type=thread_type)
            elif message_text == "view lock":
                subprocess.run("echo -n -e '\x01' > /dev/udp/192.168.1.82/1727", shell=True)
                self.send(Message(text="Lock message sent"), thread_id=thread_id, thread_type=thread_type)

def startupClient(email, password):
    try:
        with open("session.txt", "r") as session:
            session_cookies = json.loads(session.read())
    except FileNotFoundError:
        session_cookies = None

    client = HydroBot(email, password, session_cookies=session_cookies)
    with open("session.txt", "w") as session:
        session.write(json.dumps(client.getSession()))
    return client

### Reving up the engines ###
creds = config()
print(creds)
client = startupClient(creds['email'], creds['password'])
client.listen()

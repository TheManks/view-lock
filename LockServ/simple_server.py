import random as rand
import subprocess
from pathlib import Path


from flask import Flask, render_template, request
app = Flask(__name__)

@app.route("/asd")
def hello():
    return "Hello world"
   

@app.route("/")
def json():
    return render_template('json.html')
    
@app.route("/lock")
def lock():
    subprocess.run("echo -n -e '\x01' > /dev/udp/192.168.1.82/1727", shell=True)
    return "done"

@app.route("/unlock")
def unlock():
    subprocess.run("echo -n -e '\x02' > /dev/udp/192.168.1.82/1727", shell=True)
    return "done"

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8080, debug=True)

from flask import Flask
import datetime
import json

app = Flask(__name__)
number = 0
click_stack = []
n_clicks = 0
with open("class_data.csv", "a") as class_data:
        class_data.write("New Session\n")
        class_data.close()
@app.route("/")
def hello():
    return "hello world"

@app.route("/count")
def count():
    global number
    number+=1
    return str(number)

@app.route("/docs/<test>")
def docs(test):
    return test + " this is documentation"


@app.route("/click")
def test():
    global click_stack
    global n_clicks
    n_clicks += 1
    click_stack.append({"click #"+str(n_clicks):str(datetime.datetime.now())})
    with open("class_data.csv", "a") as class_data:
        class_data.write(str(n_clicks) + "," + str(datetime.datetime.now()) + "\n")
        class_data.close()
    return "done."

@app.route("/click/get")
def get_clicks():
    return json.dumps(click_stack)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0') 
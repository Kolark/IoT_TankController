from flask import Flask, render_template, jsonify, redirect, url_for, session
from functools import wraps
app = Flask(__name__)

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        # **Crucial Check:** Replace 'is_authenticated' and 'user_id'
        # with how your specific authentication system tracks login status.
        # This often involves checking a session variable or a current_user object
        # provided by an extension like Flask-Login.
        # if session.get('user_id') is None:
        #     # If not logged in, redirect to the login page
        #     return redirect(url_for('login', next=request.url))
        print("checking login...")
        return f(*args, **kwargs)
    return decorated_function

@app.route('/')
def home():
    return render_template("index.html")

@app.route('/manage')
@login_required
def manage():
    return render_template("manage.html")

@app.route('/add')
@login_required
def add():
    return render_template("add.html")

if __name__ == '__main__':
        app.run(debug=True,host='0.0.0.0', port=5000)

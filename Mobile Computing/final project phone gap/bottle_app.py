
#imports for template, posting, and routing
from bottle import default_app, route, template, post, get, request

import sqlite3

db = sqlite3.connect("./mysite/politicianBase.db")
c = db.cursor()

#route to question page
@route('/')
def userQuestions():
    return template("userQuestions.html", c = c)

@post('/compareResults')
def compareResults():
    userName = request.forms.get("userName")
    userName = str(userName)
    if (userName == 'Admin'):
        return template("menu.html")
    else:
        return template("compareResults.html", c = c)
@route('/menu')
def menu():
    return template("menu.html")

#route to show table
@route('/show/politicians')
def showAccounts():
    return template("showAccounts.html", c = c)

@route('/show/staticResponses')
def showStaticResponses():
    return template("showStaticResponses.html", c = c)

#get form data to add politician
@get('/add/politician')
def addAccountForm():
    return template("addAccount.html", c = c)

#parse and send data here
@post('/add/politician')
def addAccountResult():
    return template("addAccountResult.html", db = db, c = c)

#get form data to delete politician
@get('/delete/politician')
def deleteAccount():
    return template("deletePolitician.html", c = c)

#send form data to delete politician
@post('/delete/politician')
def deleteAccountResult():
    return template("deletePoliticianResult.html", db = db, c = c)

@get('/edit/politician')
def editAccount():
    return template("editPolitician.html", c = c)
@post('/edit/politician')
def editAccountResult():
    return template("editPoliticianResult.html", c = c)
@post('/edit/politician/complete')
def editAccountComplete():
    return template("editPoliticianComplete.html", db = db, c = c)
@get('/search/politicians')
def searchAccounts():
    return template('searchPoliticians.html')
@post('/search/politicians')
def searchResult():
    return template('searchResult.html', c = c)
application = default_app()
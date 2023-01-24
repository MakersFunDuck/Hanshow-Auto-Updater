'''
    Snipping Tool with Tkinter / Neir
    
    Part of 100 GUI Apps Challenge
    (https://github.com/besnoi/pyApps)

    Challenge Rules :
        1. App must be useful
        2. App must be beautiful
        3. App must be short (<500 LOC)
    
    And lastly no Plagiarism :D
'''
import pickle
import webbrowser
import os
import tkinter
import pyautogui
import pygame
import time
import mouse
#from tkinter import filedialog
from customtkinter import *
# importing json library
import json
import hashlib
from urllib.request import urlopen, Request



set_appearance_mode("Dark") 

win = CTk()
win.title("Hanshow Screen updater")
win.attributes("-alpha", 0.90)
win.geometry("450x300")
win.resizable(False, False)

# we need a seperate semi-transparent window for rectangular snip
board = tkinter.Toplevel(win)
# hide this window at start (we will only open it in snip mode)
board.withdraw()
# we need a GLOBAL canvas object to draw upon
canvas = None
startX,startY=None,None #to track starting pos
curX,curY=None,None #to track mouse cur pos
# we need a rectangle to define the selection snip
snipRect = None












# hide the main window and open the board
def enterSnipMode():
    #input variable

    file_exists = os.path.exists('variables.json')

    if (file_exists ==0):
        input_dictionary = {"website" : "null", "delay" : 0, "Tag name" : 0,  "Check Changes" : 0, "Background": 0, "x" : 0, "y" : 0,"w" : 0,"h" : 0, "file path" : 0, "mouse" : "", "currentHash" : 1}

        file = open("variables.json", "w")
        file.write(json.dumps(input_dictionary))

        file.close()
        print("Is JSON file created? :" + str(file_exists))
    else:
        f = open('variables.json', 'r') 

        input_dictionary = json.load(f)
        print (input_dictionary)   
        print("Is JSON file created? :" + str(file_exists))

    if (input_dictionary["Background"]): 
    
        win.withdraw() 
   

   
    if (input_dictionary["file path"]==0):
        webbrowser.open(URL.get()) 
        input_dictionary["website"]
    else:
        webbrowser.open(input_dictionary["website"])


    
    time.sleep(1)
    pyautogui.press('f11')






    if (input_dictionary["file path"]==0):  
        
        mouserec = mouse.record(button='right',)
        with open('config.dictionary', 'wb') as config_dictionary_file:  
            pickle.dump(mouserec, config_dictionary_file)    

        input_dictionary["mouse"] = mouserec[:-1]
        input_dictionary["delay"] = int(delay.get())
        
        file = open("variables.json", "w")
        file.write(json.dumps(input_dictionary))

        file.close() 
        global canvas
        win.withdraw()
        board.deiconify()
        canvas = tkinter.Canvas(board,cursor='cross',bg='grey11')
        canvas.pack(fill=BOTH, expand=YES)
        canvas.bind("<ButtonPress-1>", mousePress)
        canvas.bind("<B1-Motion>", mouseMove)
        canvas.bind("<ButtonRelease-1>", mouseRelease)
        board.bind("<Escape>", escapeSnipMode)
        board.lift()
        board.attributes('-fullscreen', True)
        board.attributes('-alpha', 0.25)
        board.attributes("-topmost", True)

            
        
        
        
        
        
        
        
    else:
        
        
        f = open('variables.json', 'r') 
        input_dictionary = json.load(f)   
        #replay mouse
        with open('config.dictionary', 'rb') as config_dictionary_file:
 
        
            mouserec = pickle.load(config_dictionary_file)
 
         # After config_dictionary is read from file
        #print(mouserec)
        
        mouse.play(mouserec[:-1])
        #global canvas
        win.withdraw()

       # canvas = tkinter.Canvas(board,cursor='cross',bg='grey11')
        #canvas.pack(fill=BOTH, expand=YES)
        rectSnip(input_dictionary["x"], input_dictionary["y"], input_dictionary["w"], input_dictionary["h"])
        

 
    
# save rectangular snip
def rectSnip(x, y, w, h):

   
    f = open('variables.json', 'r') 

    input_dictionary = json.load(f)
    print (input_dictionary)
    
    if (input_dictionary["file path"]==0):  
        
   
        board.withdraw()
        pygame.mixer.Sound('click.wav').play()
        myScreenshot = pyautogui.screenshot(region=(x, y, w, h))
        print (x,y,w,h)
        pyautogui.hotkey('ctrl','w')
        
        
        
        file_path = os.getcwd()
        if len(file_path)>5:
            myScreenshot.save((file_path+'\\capture.png'))

        print (file_path)
       # win.destroy()
        sendTag()
        
        input_dictionary.update ({"x" : x, "y" : y, "w" : w, "h" : h, "file path" : file_path, "delay" : delay.get(), "website" : URL.get(), "Tag name" :TagName.get(), "Check Changes" : cb2.get(), "Background": cb3.get() })

        file = open("variables.json", "w")
        file.write(json.dumps(input_dictionary))

        file.close()  
        if (input_dictionary["Background"]): 
            win.withdraw() 
        else:
            board.deiconify()
        
    else:
       # mouse.play( input_dictionary["mouse"])  
        myScreenshot = pyautogui.screenshot(region=(x, y, w, h))
        print (x,y,w,h)
        pyautogui.hotkey('ctrl','w') 
        
        if len(input_dictionary["file path"])>5:
            myScreenshot.save((input_dictionary["file path"]+'\\capture.png'))
        print (input_dictionary["file path"])

        sendTag()
        if (input_dictionary["Background"]): 
            win.withdraw() 
           
        else:
            board.deiconify()
        time.sleep(int(input_dictionary["delay"])) 
        
           
    

         
    
 
    
    

def mouseMove(event):
    global snipRect,startX,startY,curX,curY
    startX,startY = (event.x, event.y)
    # expand rectangle as you drag the mouse
    canvas.coords(snipRect, startX, startY, curX, curY)
    return 'break'

def mousePress(event):
    global snipRect,startX,startY,curX,curY
    startX=curX=canvas.canvasx(event.x)
    startY=curY=canvas.canvasy(event.y)
    snipRect = canvas.create_rectangle(startX,startY, 2, 2, outline='red', width=3, fill="white")
    return 'break'

def escapeSnipMode(_):
    canvas.destroy()
    board.withdraw()
    win.deiconify()

def mouseRelease(event):
    global startX,startY,curX,curY
    # for left-down, right-up, right-down and left-up
    if startX <= curX and startY <= curY:
        rectSnip(startX, startY, curX - startX, curY - startY)
    elif startX >= curX and startY >= curY:
        rectSnip(curX, curY, startX - curX, startY - curY)
    elif startX >= curX and startY <= curY:
        rectSnip(curX, startY, startX - curX, curY - startY)
    elif startX <= curX and startY >= curY:
        rectSnip(startX, curY, curX - startX, startY - curY)
    escapeSnipMode(0)
    return 'break'

def canDelay(v):
  
    delay.configure(state='normal')
    cb.configure(state='normal')


def sendTag():
    f = open('variables.json', 'r') 
    input_dictionary = json.load(f) 
    #pyautogui.press('right')
    
    
    if (input_dictionary["Check Changes"]==0):
        sendprinter = 'Python print.py '+'--devicename ' +str(input_dictionary["Tag name"]) +' capture.png'
    
        os.system(sendprinter)    
    print("One loop completed")
    
    if (input_dictionary["Check Changes"]):
         #setting the URL you want to monitor
        url = Request(input_dictionary["website"],
              headers={'User-Agent': 'Mozilla/5.0'})
 
        # to perform a GET request and load the
        # content of the website and store it in a var
        response = urlopen(url).read()
 
        # to create the initial hash
        if (input_dictionary["currentHash"]):
            input_dictionary["currentHash"] = hashlib.sha224(response).hexdigest()
            print("creating hash")
            #time.sleep(10)


        # create a new hash
        newHash = hashlib.sha224(response).hexdigest()
    
        # check if new hash is same as the previous hash
        if newHash == input_dictionary["currentHash"]:
            time.sleep(int(input_dictionary["delay"])) 
            sendTag()
               
 
        # if something changed in the hashes
        else:
            # notify
            print("something changed in the website")
 
            # again read the website
            response = urlopen(url).read()
 
            # create a hash
            input_dictionary["currentHash"] = hashlib.sha224(response).hexdigest()

            sendprinter = 'Python print.py '+'--devicename ' +str(input_dictionary["Tag name"]) +' capture.png'
    
            os.system(sendprinter)    
            print("One loop completed") 

            
 

    
   


### Init Layout

CTkLabel(master=win,text='Enter Price Tag Name:').grid(row=0,column=0,pady=10,padx=0,sticky='we')
TagName = CTkEntry(master=win,width=40)
TagName.grid(row=0,column=1,pady=10,padx=30,sticky='we')



CTkLabel(master=win,text='Enter URL:').grid(row=1,column=0,pady=10,padx=0,sticky='we')
URL = CTkEntry(master=win,width=40)
URL.grid(row=1,column=1,pady=10,padx=30,sticky='we')


cb = CTkCheckBox(master=win,text='Screen Update (minutes)')
cb.grid(row=2,column=0,pady=10,padx=30,sticky='we')
delay = CTkEntry(master=win,width=40)
delay.grid(row=2,column=1,pady=10,padx=30,sticky='we')

cb2 = CTkCheckBox(master=win,text='Check changes')
cb2.grid(row=3,column=0,pady=10,padx=30,sticky='we')
cb3 = CTkCheckBox(master=win,text='Work in background')
cb3.grid(row=3,column=1,pady=10,padx=30,sticky='we')



CTkButton(master=win, text="Snip",height=48,command=enterSnipMode).grid(row=4,column=0,columnspan=2,pady=10,padx=30,sticky='we')

pygame.init()

input_dictionary = {"Background" : 0}
file_exists = os.path.exists('variables.json')

if (file_exists ==1):
    f = open('variables.json', 'r') 
    input_dictionary = json.load(f)   

while (input_dictionary["Background"]): 
    
    win.withdraw() 
    enterSnipMode()
win.mainloop()

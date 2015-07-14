#********** Static calculation of maximum stack *********#

#Tkinter to display the maximum stack required for a function in a window
#re is regular expression used to match,sub and to search the required string
#glob to open a file from specific folder
#os to create the file in a specific folder or directory
#defaultdict is used to store many values in a single dictionary
import Tkinter,re,glob,os
from Tkinter import *
from collections import defaultdict

#stringTok function takes line as input and
#toke the line to get the function Name
#returns only the function name
def stringTok(line):            
    fxname=re.match("(.*)<(.*)>",line)
    fxname=fxname.group(2)
    return fxname

#computeStack stores the stack required for the path in a compStack array
#travPath contains path and using that path the function finds the stack
#required for the path and stores it in an array
def computeStack(travPath):
    stack=0
    for i in range(len(travPath)):
        fxnName=travPath[i]
        stack=dictfxnInfo[fxnName][1]+stack
    compStack.append(stack)
    return

#getIndexValue takes maximumStack value
#returns the index of the maximum stack value in a compStack array 
def getIndexValue(maximumStack):
    for i in range(len(compStack)):
        if compStack[i]==maximumStack:
            return i
    return -1

#getFxnInfoInDict takes empty dictionary and function name as input
#This function Stores all the required values in a dictionary and returns the dictionary
#function name is the key of the dictionary, if name not exists program stops
#number of lines, Offset and stack for function are the values of the dictionary
def getFxnInfoInDict(dictfxnInfo,fxnName):
    offset=Numline=check=stack=checkNameExists=0
    tempName=""
    for line in f:
        Numline+=1
        if re.match("[0-9,a-z]+[ ]+.*",line) :  
            FxnName=stringTok(line)
            if FxnName==fxnName:
                checkNameExists+=1
            check=1
            dictfxnInfo[FxnName].append(int(offset))
            dictfxnInfo[tempName].append(Numline)
            Numline=0
            tempName=FxnName
        offset+=len(line)+1
        if check!=0:
            if re.search("push\t{r7",line):     
                if re.search("lr",line):  
                    stack=8
                else:
                    stack=4
            if re.search("sub\t", line):
                num = re.sub(r'.*[0-9,a-z]+[ ].* #', "",line)
                num = re.sub(r'; .*', "", num)
                stack+=int(num)
            if Numline==2:
                dictfxnInfo[FxnName].append(stack)
                check=0
    dictfxnInfo[tempName].append(Numline)
    if checkNameExists==0:
        print "Function name entered is wrong"
        exit(0)
    return dictfxnInfo

#getAllPath function finds all the paths in a given function,it takes function name, travPath and compPath array
#considering all the factors (number of lines, offset bytes and stack for a function name) and store them
#checking for the presence of recursive function, If present neglect the path and continue with other paths
#If there is no sub function it indicates path is completed so store the path and stack for the path
#pop the last function and return to find next path
def getAllPath(fxnName,travPath,compPath):  
    offset=dictfxnInfo[fxnName][0]
    lines=dictfxnInfo[fxnName][2]
    count=blSeen=addOff=stack=0
    if fxnName in travPath:        
        count=lines
    travPath.append(fxnName)
    f.seek(offset)
    while(count!=lines):
        line=f.readline()
        addOff+=len(line)+1
        if re.search("bl\t",line):         
            getAllPath(stringTok(line),travPath,compPath)
            f.seek(offset+int(addOff))
            blSeen+=1
        count+=1
    if(blSeen==0):
        string=""        
        for i in range(len(travPath)):
            string=string+" "+travPath[i]
        compPath.append(string)
        computeStack(travPath)
    travPath.pop()
    return

#showThePathInTextFile function stores all the path and maximum stack in a file
#User enters the path where the file to be created
#Using the compPath list we store all the paths in a file
#we also store the maximum stack required for the function and also the corresponding path
def showThePathInTextFile(compPath,fxnName,maximumStack):
    print "Enter the path to store the file"
    path=raw_input()
    filepath = os.path.join(path, "storePath.txt")
    if not os.path.exists(path):
        os.makedirs(path)
    f1 = open(filepath, "w")
    f1.write("*****Paths present in the Function: <")
    f1.write(fxnName)
    f1.write(">*****\n\n")
    previousPath=currentPath=""
    for i in range(len(compPath)):
        currentPath=compPath[i].split()
        count=0
        if i>0:
            previousPath=compPath[i-1].split()
            for i in range(len(previousPath)):
                if i==(len(currentPath)-1):
                    break
                if currentPath[i]==previousPath[i]:
                    count+=1
                    f1.write("\t  ")
        i=count
        while i in range(len(currentPath)):
            f1.write("|--> ")
            f1.write(currentPath[i])
            f1.write("\n\n")
            if i!=0 and i!=len(currentPath)-1:
                for j in range(i+1):
                    f1.write("\t  ")
            if i==0:
                f1.write("\t  ")
            i+=1
    f1.write("\n\nMaximum stack path of the given function is:\n\n")
    index=0
    index=getIndexValue(maximumStack)
    if index!=-1:
        currentPath=compPath[index].split()
        for item in currentPath:
            f1.write("--> ")
            f1.write(item)
        f1.write("\n\nMaximum stack required for the given function is:\t")
        f1.write(str(maximumStack))
        f1.close()
    return

#displayMaxStackValue function displays the maximum stack value in a window   
def displayMaxStackValue(maximumStack):
    maxStWnd= Tk()
    Label(maxStWnd, 
        text="Maximum stack require for Program is",
        fg="blue",bg="yellow",height=2,
        ).pack(side=TOP,padx=20)
    Label(maxStWnd, 
        text=maximumStack,
        fg="blue",bg="green",height=2,
        ).pack(side=LEFT,padx=50)
    Label(maxStWnd, 
        text="bytes",
        fg="blue",bg="green",height=2,
        ).pack(side=LEFT,padx=20)
    maxStWnd.mainloop()

#User enters the path for the file where assembly file of .elf exists
#User enters the function name to find maximum stack
#travPath stores all the function names in a path
#compPath and compStack stores one complete path and stack for the path respectively
if __name__ == "__main__":
    print ("Enter the path of the file")
    path=raw_input()    
    files=glob.glob(path)
    for file in files:     
        f=open(file,'r')
    print ("Enter function name")
    fxnName=raw_input()
    dictfxnInfo=defaultdict(list)
    dictfxnInfo=getFxnInfoInDict(dictfxnInfo,fxnName)
    travPath=[]  
    compPath=[]   
    compStack=[]
    getAllPath(fxnName,travPath,compPath)
    maximumStack=max(compStack)
    showThePathInTextFile(compPath,fxnName,maximumStack)
    displayMaxStackValue(maximumStack) 

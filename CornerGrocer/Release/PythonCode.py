import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

#Function that is used to Open the File "InputFile" and assign the information stored in the file as a list
#The list is then seperated into a new list that only contains one of each item sold
#Finally another list is created to hold the number of times each item was sold
#Returns the list of each item plus the list of values as one list
def ReadFile():
    f = open("InputFile.txt", "r") #Opens the file and assigns the file to a variable
    itemList = [] #List that will hold all information from the file
    groceryList = [] #List that will hold just the name of each individual item on the list
    count = 0 #Used as an iterator in a for loop
    value = [] #List that will hold the number of times an item was sold

    #For loop that assigns each line in the file to the items list
    for x in f:
        itemList.append(x.strip())#.strip is used to remove the new line from the list

    #For loop that assigns each individual item in groceryList ensuring there is no duplicates
    for item in itemList:
        if item not in groceryList:
            groceryList.append(item)

    #For loop that iterates through the items in groceryList and checks for the number of times mentioned in the items list 
    for grocery in groceryList:
        count = 0 #Iterator that keeps track of the location in the for loop
        #For loop that iterates through the items list to check the number of times an item was sold
        for item in itemList:
            #If the grocery item matches the item in items list add one to the count
            if(grocery == item):
                count = count + 1
        value.append(count) #At the end of the inner for loop add the count to the value list

    f.close() #Closes the file 
    return groceryList + value

#Function that takes in the list from the ReadFile function and prints the items with there quantity sold
def PrintList():
    itemList = ReadFile() #List that holds the combined lists of groceryList and valueList
    index = 0 #Iterator for the while loop
    groceryList = [] #Will hold the item's names
    valueList = [] #Will hold the item's quantity

    #While loop that will be used to iterate through the combined list and sort the list into the groceryList and the valueList
    while index < len(itemList):
        #The first half of the list is the item names and will be stored in groceryList
        if(index < (len(itemList) / 2)):
            groceryList.append(itemList[index])
        #The second half of the list is the item quantity and will be stored in valueList
        else:
            valueList.append(itemList[index])
        index = index + 1 #Increase the index to move to the next index in the list

    index = 0 #Reset the iterator for a new while loop

    #While loop that prints the two list concatenated
    while index < len(groceryList):
        print(groceryList[index] + ": " + str(valueList[index]))
        index = index + 1 #Increase the index to move to the next index in the list

#Function that takes in the list from the ReadFile function and a parameter to find the number of times a certain item was sold
#Parameter - input as a user entered string
#Returns - 1 as an integer to notify the user that the function was called
def SpecificItem(userInput):
    itemList = ReadFile() #List that holds the combined lists of groceryList and valueList
    index = 0 #Iterator for the while loop
    groceryList = [] #Will hold the item's names
    valueList = [] #Will hold the item's quantity
    yes = 0 #Value to check if the item has sold in the list 0 for no and 1 for yes

    #While loop that will be used to iterate through the combined list and sort the list into the groceryList and the valueList
    while index < len(itemList):
        #The first half of the list is the item names and will be stored in groceryList
        if(index < (len(itemList) / 2)):
            groceryList.append(itemList[index])
        #The second half of the list is the item quantity and will be stored in valueList
        else:
            valueList.append(itemList[index])
        index = index + 1 #Increase the index to move to the next index in the list

    index = 0 #Reset the iterator for a new while loop

    #While loop that searches for the user entered word and prints the item name and the times it was sold
    while index < len(groceryList):
        #Checks if the user entered word matches the item at the index in groceryList
        if(userInput == groceryList[index]):
            print(groceryList[index] + " sold " + str(valueList[index]) + " times")
            yes = 1 #Item was sold sets yes to 1
        #If the while loop is at the end of the list and yes is still 0 then the item was not sold
        elif(index == (len(groceryList) - 1) and yes == 0):
            print(userInput + " was not sold today")
        index = index + 1 #Increase the index to move to the next index in the list

    return 1

#Function that calls the ReadFile function to get the list of grocery items and the list of their quantities
#Creates two lists to store the items and their quantities 
#Creates a new file named "frequency.dat" and writes the items and their quantities to the File
#Returns the length of the groceryList for the Histogram function
def WriteFile(fileName):
    f = open(fileName, "w") #Opens the file and assigns the file to a variable
    itemList = ReadFile() #List that will hold all information to be printed to the file
    groceryList = [] #List that will hold just the name of each individual item on the list
    index = 0 #Used as an iterator in a for loop
    valueList = [] #List that will hold the number of times an item was sold

    #While loop that will be used to iterate through the combined list and sort the list into the groceryList and the valueList
    while index < len(itemList):
        #The first half of the list is the item names and will be stored in groceryList
        if(index < (len(itemList) / 2)):
            groceryList.append(itemList[index])
        #The second half of the list is the item quantity and will be stored in valueList
        else:
            valueList.append(itemList[index])
        index = index + 1 #Increase the index to move to the next index in the list

    index = 0 #Reset the iterator for a new while loop

    #While loop that writes the two lists concatenated to the file
    while index < len(groceryList):
        f.write(groceryList[index] + " " + str(valueList[index]) + "\n")
        index = index + 1 #Increase the index to move to the next index in the list

    f.close() #Closes the file 
    return len(groceryList)

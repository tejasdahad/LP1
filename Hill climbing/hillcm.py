import string
import random

def score(list1,list2):
    score_gen = 0
    for i in range(len(list1)):
        if list1[i] == list2[i]:
            score_gen = score_gen+1
    return score_gen / len(list1)
    
def create(clist,list1,list2):
    for i in range(len(list1)):
        if list1[i] == list2[i]:
            clist[i] = list1[i]
    return clist
    
def random_generator(goal):
#    characters = string.ascii_lowercase+" "
 #   randstring = ""
  #  for i in range(len(goal)):
   #     randstring = randstring + characters[random.randrange(len(characters))]
   # randList = [randstring[i] for i in range(len(randstring))]
    randList = [random.choice(string.printable) for _ in range(len(goal))]
    return randList
    
def main():
    goal = "my name is pratik"
    goallist = [goal[i] for i in range(len(goal))]
    clist = [' ' for i in range(len(goal))]
    random_string = random_generator(goallist)
    clist = create(clist,random_string,goallist)
    score_gen = score(clist,goallist)
    iteration = 0
    while (score_gen < 1):
        random_string = random_generator(goallist)
        clist = create(clist,random_string,goallist)
        score_gen = score(clist,goallist)
        iteration = iteration+1
        print(score_gen," : ",''.join(clist))
    print("Total iterations: ",iteration)
    
main()
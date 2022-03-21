import collections

users = {}
transactions = []

#get data from user
txt = input()
stxt = txt.split()
user_no  = int(stxt[0])
transaction_no = int(stxt[1])

for x in range(0, user_no):
    txt = input()
    stxt = txt.split()
    username = stxt[0]
    balance = int(stxt[1])
    users[username] = balance

for y in range(0, transaction_no):
    txt = input()
    stxt = txt.split()
    user_a= stxt[0]
    user_b = stxt[1]
    amount = int(stxt[2])
    trans = {
        "user_a" : user_a,
        "user_b" : user_b,
        "amount" : amount
    }
    transactions.append(trans)

#perform calculations
for transaction in transactions :
    if (users[transaction['user_a']] > transaction["amount"]): 
        users[transaction['user_a']] -= transaction["amount"]
        users[transaction['user_b']] += transaction["amount"]

#sort according to username
ordered_users = collections.OrderedDict(sorted(users.items()))

# output = [user_no,balance]
for key , value in ordered_users.items():
    print(key, value)

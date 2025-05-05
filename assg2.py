hashtable = [] 
size = 0 
bucket = {} 
 
def create(): 
    global size 
    size = int(input("ENTER SIZE OF TABLE: ")) 
    for i in range(size): 
        hashtable.append([None, -1]) 
    bucket[0] = -1 
 
def printtable(): 
    for i in range(size): 
        print(f"Index {i}: Key = {hashtable[i][0]}, Chain = {hashtable[i][1]}")

def display():
    print("\nHASH TABLE STATE:")
    for i in range(size):
        key = hashtable[i][0]
        chain = hashtable[i][1]
        if key is not None:
            chain_str = f" -> {chain}" if chain != -1 else ""
            print(f"[{i}] Key: {key}{chain_str}")
        else:
            print(f"[{i}] Empty")
    print()

def insert(key): 
    global size 
    hash = key % size 
 
    if hashtable[hash][0] is None: 
        hashtable[hash][0] = key 
        bucket[key % size] = hash 
    else: 
        for i in range(size): 
            hash = (key + i) % size 
            if hashtable[hash][0] is None: 
                hashtable[hash][0] = key 
                bucket[key % size] = hash 
                if bucket[key % size] != -1: 
                    hashtable[bucket[key % size]][1] = hash 
                    bucket[key % size] = hash 
                return 
        print("KEY", key, "NOT INSERTED AS HASH TABLE IS FULL") 
 
def search(key): 
    hash = key % size 
    if hashtable[hash][0] == key: 
        print("KEY", key, "FOUND AT INDEX", hash) 
    else: 
        i = 0 
        chain = hashtable[hash][1] 
        while chain != -1: 
            if hashtable[chain][0] == key: 
                print("KEY", key, "FOUND AT INDEX", chain) 
                return 
            chain = hashtable[chain][1] 
        print("KEY NOT FOUND") 
 
def delete(key): 
    hash = key % size 
    if hashtable[hash][0] == key: 
        hashtable[hash][0], hashtable[hash][1] = None, -1 
        print("KEY", key, "WAS DELETED FROM INDEX", hash) 
    else: 
        chain1, chain2 = hash, hashtable[hash][1] 
        while chain2 != -1: 
            if hashtable[chain2][0] == key: 
                hashtable[chain1][1] = hashtable[chain2][1] 
                hashtable[chain2][0], hashtable[chain2][1] = None, -1 
                print("KEY", key, "WAS DELETED FROM INDEX", chain2) 
                return 
            chain1, chain2 = chain2, hashtable[chain2][1] 
        print("KEY NOT FOUND") 
 
def replace(key): 
    hash = key % size 
    if hashtable[hash][0] is None or hashtable[hash][0] % size == key % size: 
        insert(key) 
    else: 
        x = hashtable[hash][0] 
        delete(x) 
        insert(key) 
        insert(x) 
 
create() 
while True: 
    print('''\nMAIN MENU:
1. WITHOUT REPLACEMENT 
2. WITH REPLACEMENT 
3. EXIT''') 
    ch = int(input("ENTER YOUR CHOICE: ")) 
     
    if ch == 1: 
        while True: 
            print('''\nWITHOUT REPLACEMENT MENU:
1. INSERT 
2. SEARCH 
3. DELETE 
4. DISPLAY
5. BACK''') 
            ch2 = int(input("ENTER YOUR CHOICE: ")) 
            if ch2 == 1: 
                key = int(input("ENTER KEY TO BE INSERTED: ")) 
                insert(key) 
                display() 
            elif ch2 == 2: 
                key = int(input("ENTER KEY TO BE SEARCHED: ")) 
                search(key) 
                display() 
            elif ch2 == 3: 
                key = int(input("ENTER KEY TO BE DELETED: ")) 
                delete(key) 
                display() 
            elif ch2 == 4: 
                display()
            elif ch2 == 5: 
                break 
            else: 
                print("ENTER VALID CHOICE") 
     
    elif ch == 2: 
        while True: 
            print('''\nWITH REPLACEMENT MENU:
1. INSERT 
2. SEARCH 
3. DELETE 
4. DISPLAY
5. BACK''') 
            ch2 = int(input("ENTER YOUR CHOICE: ")) 
            if ch2 == 1: 
                key = int(input("ENTER KEY TO BE INSERTED: ")) 
                replace(key) 
                display() 
            elif ch2 == 2: 
                key = int(input("ENTER KEY TO BE SEARCHED: ")) 
                search(key) 
                display() 
            elif ch2 == 3: 
                key = int(input("ENTER KEY TO BE DELETED: ")) 
                delete(key) 
                display() 
            elif ch2 == 4:
                display()
            elif ch2 == 5: 
                break 
            else: 
                print("ENTER VALID CHOICE") 
    elif ch == 3: 
        print("EXITING") 
        break 
    else: 
        print("ENTER VALID CHOICE")

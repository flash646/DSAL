class Hashtable:
    def __init__(self, key, link):
        self.key = key
        self.link = link  # Points to next index in the chain

class Table:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def hash_function(self, key):
        return key % self.size

    def insert(self, key, link=-1):
        index = self.hash_function(key)

        # If main spot is empty
        if self.table[index] is None:
            self.table[index] = Hashtable(key, link)
            return index

        # Collision occurred
        print("Collision occurred")

        # If key at hashed index doesn't belong there (replacement required)
        if self.hash_function(self.table[index].key) != index:
            displaced = self.table[index]
            self.table[index] = Hashtable(key, -1)
            new_index = self.insert(displaced.key, displaced.link)

            # Update any existing chain that pointed to the old index
            for i in range(self.size):
                if self.table[i] and self.table[i].link == index:
                    self.table[i].link = new_index
                    break
            return index

        # Linear probing with chaining
        i = (index + 1) % self.size
        while i != index:
            if self.table[i] is None:
                self.table[i] = Hashtable(key, link)
                # Link it to the chain
                for j in range(self.size):
                    if self.table[j] and self.table[j].link == -1 and self.hash_function(self.table[j].key) == index:
                        self.table[j].link = i
                        break
                return i
            i = (i + 1) % self.size
        print("Table is full!")
        return -1

    def search(self, key):
        index = self.hash_function(key)
        while index != -1:
            if self.table[index] and self.table[index].key == key:
                return index
            index = self.table[index].link if self.table[index] else -1
        return None

    def delete(self, key):
        index = self.search(key)
        if index is not None:
            self.table[index] = None
            print(f"Deleted key {key} from index {index}")
        else:
            print("Key not found!")

    def display(self):
        print("\nIndex : Key -> Link")
        for i in range(self.size):
            if self.table[i]:
                print(f"{i} : {self.table[i].key} -> {self.table[i].link}")
            else:
                print(f"{i} : -")

def main():
    size = int(input("Enter hash table size: "))
    ht = Table(size)

    while True:
        print("\n1: Insert\n2: Display\n3: Search\n4: Delete\n-1: Exit")
        choice = int(input("Enter choice: "))

        if choice == 1:
            key = int(input("Enter key to insert: "))
            ht.insert(key)
        elif choice == 2:
            ht.display()
        elif choice == 3:
            key = int(input("Enter key to search: "))
            index = ht.search(key)
            print(f"Key found at index {index}" if index is not None else "Key not found.")
        elif choice == 4:
            key = int(input("Enter key to delete: "))
            ht.delete(key)
        elif choice == -1:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Try again.")

if __name__ == "__main__":
    main()

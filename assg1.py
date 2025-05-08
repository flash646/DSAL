class Record:
    def __init__(self, name="", number=0):
        self.name = name
        self.number = number

    def __str__(self): #special method in Python used to define a string representation
        return f"Name: {self.name}\tNumber: {self.number}"


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size
        self.count = 0

    def is_full(self):
        return self.count == self.size

    def hash_function(self, key):
        return key % self.size

    # ---------- LINEAR PROBING INSERT FUNCTION ----------
    def insert(self, record):
        if self.is_full():
            print("Hash Table is full!")
            return

        pos = self.hash_function(record.number)
        start = pos

        # Check for collision
        if self.table[pos] is not None:
            print("Collision occurred")

        # Linear Probing starts here
        while self.table[pos] is not None:
            pos = (pos + 1) % self.size
            if pos == start:
                print("No empty slot found!")
                return

        self.table[pos] = record
        self.count += 1
        print(f"{record.name}'s number inserted at position {pos}")

    def search(self, name):
        for i in range(self.size):
            if self.table[i] and self.table[i].name == name:
                print(f"Found at position {i}")
                return i
        print("Record not found.")
        return None

    def display(self):
        print("\nHash Table:")
        for i, record in enumerate(self.table):
            print(f"Index {i}: {record}")
        print(f"Total records: {self.count}")


class DoubleHashTable(HashTable):
    def second_hash(self, key):
        return 5 - (key % 5)

    # ---------- DOUBLE HASHING INSERT FUNCTION ----------
    def insert(self, record):
        if self.is_full():
            print("Hash Table is full!")
            return

        pos = self.hash_function(record.number)

        if self.table[pos] is not None:
            print("Collision occurred")

        if self.table[pos] is None:
            self.table[pos] = record
            print(f"{record.name}'s number inserted at position {pos}")
        else:
            step = self.second_hash(record.number)
            for i in range(1, self.size + 1):
                new_pos = (pos + i * step) % self.size
                if self.table[new_pos] is None:
                    self.table[new_pos] = record
                    print(f"{record.name}'s number inserted at position {new_pos}")
                    break

        self.count += 1

    def search(self, name):
        for i in range(self.size):
            if self.table[i] and self.table[i].name == name:
                print(f"Found at position {i}")
                return i
        print("Record not found.")
        return None


def get_record():
    name = input("Enter Name: ")
    number = int(input("Enter Number: "))
    return Record(name, number)


def main():
    while True:
        print("\n1. Linear Probing\n2. Double Hashing\n3. Exit")
        choice = int(input("Choose: "))

        if choice == 3:
            break

        size = int(input("Enter table size: "))
        table = HashTable(size) if choice == 1 else DoubleHashTable(size)

        while True:
            print("\n1. Insert\n2. Search by Name\n3. Display\n4. Back")
            op = int(input("Choose: "))

            if op == 4:
                break
            elif op == 1:
                table.insert(get_record())
            elif op == 2:
                name = input("Enter Name to search: ")
                table.search(name)
            elif op == 3:
                table.display()


if __name__ == "__main__":
    main()

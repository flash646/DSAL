# Program 1 ( linear Probing and Double Hashing )

class Record:
    def __init__(self):
        self.name = None
        self.number = None

    def set_data(self, name, number):
        self.name = name
        self.number = number

    def __str__(self):
        return f"Name: {self.name}\t\tNumber: {self.number}"


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size
        self.element_count = 0

    def is_full(self):
        return self.element_count == self.size

    def hash_function(self, key):
        return key % self.size

    def insert(self, record):
        if self.is_full():
            print("Hash Table Full")
            return

        pos = self.hash_function(record.number)

        if self.table[pos] is None:
            self.table[pos] = record
            print(f"Phone number of {record.name} is at position {pos}")
        else:
            print(f"Collision for {record.name}'s number at position {pos}, finding new position.")
            start = pos
            while self.table[pos] is not None:
                pos = (pos + 1) % self.size
                if pos == start:
                    print("No empty slot found")
                    return
            self.table[pos] = record
            print(f"Phone number of {record.name} is at position {pos}")

        self.element_count += 1

    def search(self, record):
        pos = self.hash_function(record.number)
        comparisons = 1

        while self.table[pos] is not None:
            if self.table[pos].name == record.name and self.table[pos].number == record.number:
                print(f"Phone number found at position {pos}, comparisons: {comparisons}")
                return pos
            pos = (pos + 1) % self.size
            comparisons += 1
            if comparisons > self.size:
                break

        print("Record not found")
        return None

    def display(self):
        print("\nHash Table:")
        for i, record in enumerate(self.table):
            print(f"Hash Value: {i}\t\t{record}")
        print(f"Total records: {self.element_count}")


class DoubleHashTable(HashTable):
    def h2(self, key):
        return 5 - (key % 5)

    def insert(self, record):
        if self.is_full():
            print("Hash Table Full")
            return

        pos = self.hash_function(record.number)

        if self.table[pos] is None:
            self.table[pos] = record
            print(f"Phone number of {record.name} is at position {pos}")
        else:
            print(f"Collision for {record.name}'s number at position {pos}, finding new position.")
            i = 1
            while i <= self.size:
                new_pos = (pos + i * self.h2(record.number)) % self.size
                if self.table[new_pos] is None:
                    self.table[new_pos] = record
                    print(f"Phone number of {record.name} is at position {new_pos}")
                    break
                i += 1

        self.element_count += 1

    def search(self, record):
        pos = self.hash_function(record.number)
        comparisons = 1

        if self.table[pos] and self.table[pos].name == record.name:
            print(f"Phone number found at position {pos}, comparisons: {comparisons}")
            return pos

        i = 1
        while i <= self.size:
            new_pos = (pos + i * self.h2(record.number)) % self.size
            comparisons += 1
            if self.table[new_pos] and self.table[new_pos].name == record.name:
                print(f"Phone number found at position {new_pos}, comparisons: {comparisons}")
                return new_pos
            i += 1

        print("Record not found")
        return None


def input_record():
    r = Record()
    name = input("Enter Name: ")
    number = int(input("Enter Number: "))
    r.set_data(name, number)
    return r


def main():
    while True:
        print("\n1. Linear Probing\n2. Double Hashing\n3. Exit")
        choice = int(input("Enter choice: "))

        if choice == 3:
            break

        size = int(input("Enter size of the hash table: "))
        ht = HashTable(size) if choice == 1 else DoubleHashTable(size)

        while True:
            print("\n1. Insert\n2. Search\n3. Display\n4. Back")
            op = int(input("Enter choice: "))
            if op == 4:
                break
            elif op == 1:
                ht.insert(input_record())
            elif op == 2:
                ht.search(input_record())
            elif op == 3:
                ht.display()


if __name__ == "__main__":
    main()

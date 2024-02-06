def main():
    struct = [0, 1, 2]
    transactions = []
    count = 0
    with open('projet.txt') as file:
        lines = file.readlines()
        for line in lines:
            if ' ' in line.strip():
                depart, arrive, etiquete = line.strip().split()
                transactions.append([depart, arrive, etiquete])
                count += 1
        struct[0] = transactions
        struct[1] = lines[count].strip()
        struct[2] = lines[count + 1].strip()
    print(struct)


if __name__ == '__main__':
    main()

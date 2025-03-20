def out(cards):
    val = []
    for i in range(len(cards)):
        sum = 0
        if '2' in cards[i]:
            sum+=150
        elif 'A' in cards[i]:
            sum+=140
        elif 'K' in cards[i]:
            sum+=130
        elif 'Q' in cards[i]:
            sum+=120
        elif 'J' in cards[i]:
            sum+=110
        elif '10' in cards[i]:
            sum+=100
        elif '9' in cards[i]:
            sum+=90
        elif '8' in cards[i]:
            sum+=80
        elif '7' in cards[i]:
            sum+=70
        elif '6' in cards[i]:
            sum+=60
        elif '5' in cards[i]:
            sum+=50
        elif '4' in cards[i]:
            sum+=40
        elif '3' in cards[i]:
            sum+=30
        
        if 'h' in cards[i]:
            sum+=4
        elif 's' in cards[i]:
            sum+=3
        elif 'd' in cards[i]:
            sum+=2
        elif 'c' in cards[i]:
            sum+=1
        val.append(sum)
    for i in range(len(cards) - 1):
        for j in range(i + 1, len(cards)):
            if val[i] < val[j]:
                val[i], val[j] = val[j], val[i]
                cards[i], cards[j] = cards[j], cards[i]
    
    for i in range(len(cards)):
        if i != len(cards) - 1:
            print(cards[i], end=" ")
        else:
            print(cards[i])

while True:
    try:
        cards = input().split()
        out(cards)
    except EOFError:
        break
import sys

answers = {
    4: 'few',
    9: 'several',
    19: 'pack',
    49: 'lots',
    99: 'horde',
    249: 'throng',
    499: 'swarm',
    999: 'zounds',
    2001: 'legion'
}
number = int(sys.stdin.readline())
for i, text in answers.items():
    if number <= i:
        print(text)
        break

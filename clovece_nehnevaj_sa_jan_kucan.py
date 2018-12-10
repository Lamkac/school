# Jan Kucan 85917
import time
import random

# globalne parametre

# pauza medzi hadzanim kocky
wait_time = 0
# pocet hracov 1 az 4
max_players = 2
# velkost hracej plochy, neparne cislo a vacsie ako 4
board_size = 11
# polovica hracej plochy
half_board = board_size // 2

# pre vypisovanie plochy

# prazdne
board_empty = "."
# domcek
board_home = "-"
# cesta
board_road = "*"
# stred
board_middle = "X"
# hrac
board_player = ["A","B","C","D"]


# prva uloha, generovat prazdnu sachovnicu
def gen_board(n):
    board = []

    for i in range(n):
        board.append([])

        for j in range(n):
            if (i < half_board or i > half_board) and ((j == half_board - 1) or (j == half_board + 1)):
                board[i].append(board_road)
            elif (j < half_board or j > half_board) and ((i == half_board - 1) or (i == half_board + 1)):
                board[i].append(board_road)
            elif j == half_board:
                if i == half_board:
                    board[i].append(board_middle)
                elif i == 0 or i == n - 1:
                    board[i].append(board_road)
                else:
                    board[i].append(board_home)
            elif i == half_board:
                if j == 0 or j == n - 1:
                    board[i].append(board_road)
                else:
                    board[i].append(board_home)
            else:
                board[i].append(board_empty)

    return board


# prva uloha, vykresli celu sachovnicu
def print_board(b):
    size = len(b)
    for i in range(size):
        for j in range(size):
            print(b[j][i] + " ", end="")
        print("")

    print("")


# najdi dalsiu poziciu
def next(position, player_id, range):
    new_position = position.copy()

    # koniec moznosti, ked prejde do stredu
    if (half_board - 2 < position[0] < half_board + 2 and position[1] == half_board) or (half_board - 2 < position[1] < half_board + 2 and position[0] == half_board):
        new_position = None

    # do domceka dole hrac 0
    elif player_id == 0 and position[0] == half_board and position[1] < half_board - 1:
        new_position[1] = new_position[1] + 1

    # do domceka vpravo hrac 1 ak hraju aspon traja
    elif player_id == 1 and max_players > 2 and position[1] == half_board and position[0] < half_board - 1:
        new_position[0] = new_position[0] + 1

    # do domceka hore hrac 2 alebo hrac 1 ak hraju len dvaja
    elif (player_id == 2 or (player_id == 1 and max_players == 2)) and position[0] == half_board and position[1] > half_board + 1:
        new_position[1] = new_position[1] - 1

    # do domceka vlavo hrac 3
    elif player_id == 3 and position[1] == half_board and position[0] > half_board + 1:
        new_position[0] = new_position[0] - 1

    # pohyb dole
    elif (position[0] == half_board + 1 and (position[1] < half_board - 1 or (half_board < position[1] < board_size - 1))) or \
            (position[0] == board_size - 1 and half_board - 2 < position[1] < half_board + 1):
        new_position[1] = new_position[1] + 1

    # pohyb vpravo
    elif position[1] == half_board - 1 and (position[0] < half_board - 1 or (half_board < position[0] < board_size - 1)) or \
            (position[1] == 0 and half_board - 2 < position[0] < half_board + 1):
        new_position[0] = new_position[0] + 1

    # pohyb hore
    elif (position[0] == half_board - 1 and (position[1] > half_board + 1 or (0 <= position[1] < half_board))) or \
            (position[0] == 0 and (half_board - 1 < position[1] < half_board + 2)):
        new_position[1] = new_position[1] - 1

    # pohyb vlave
    elif (position[1] == half_board + 1 and (position[0] > half_board + 1 or (0 <= position[0] < half_board))) or \
            (position[1] == board_size - 1 and (half_board - 1 < position[0] < half_board + 2)):
        new_position[0] = new_position[0] - 1

    if range > 1 and new_position is not None:
        new_position = next(new_position,player_id,range-1)

    return new_position


# ci sa panacik nachadza v domceku
def is_home(p):
    if (board_size - 1 > p[0] > 0 and p[1] == half_board) or (board_size - 1 > p[1] > 0 and p[0] == half_board):
        return True
    return False


# odstrani panacika z hracej plochy
def remove_player(spawn_count, players_units, position):
    for i in range(len(players_units)):
        for unit in players_units[i]:
            if position[0] == unit[0] and position[1] == unit[1]:
                spawn_count[i] = spawn_count[i] + 1
                players_units[i].remove(unit)


# skontroluje poziciu podla toho kto sa tam nachadza
def check_move(players_units, position, player_id):
    for i in range(len(players_units)):
        for unit in players_units[i]:
            if position[0] == unit[0] and position[1] == unit[1]:
                if i == player_id:
                    # ak je tam panacik rovnaky ako hraca ktory prave ide vrati 1
                    return 1
                else:
                    # ak je tam iny panacik ineho hraca tak vrati 2
                    return 2
    # ak tam nieje nic tak vrati 0
    return 0


# iba vykresli hraca na danu poziciu
def draw_player(board,position,player_id):
        board[position[0]][position[1]] = board_player[player_id]


# skontroluje ak uz niekto nevyhral ak ma v domceku kazdeho panacika
def check_win(home_count):
    for i in range(len(home_count)):
        if home_count[i] > half_board - 2:
            print("Vyhral hrac "+board_player[i])
            return True


# nastavy velkost hracej dosky pre hraciu plochu a vrati True ak velkost je mozna na hranie
def set_board_size():
    global board_size
    global half_board

    print("Zadaj velkost hracej dosky:")
    size = int(input())
    if size > 4 and size%2 == 1:
        board_size = size
        half_board = size // 2
        return True
    else:
        print("Nepodporovana velkost")
        return False


# druha uloha, hrac pojde len dookola do domceka
def druha_uloha():
    players_unit = [half_board + 1,0,0]

    board = gen_board(board_size)
    while True:
        # cakanie na tah a generovanie nahodneho cisla
        time.sleep(wait_time)
        rand = random.randint(1, 6)
        # vypis
        print("Hrac hodil cislo "+str(rand))
        next_position = next(players_unit, 0, rand)
        if next_position is not None:
            # nahradi hraca za cestu
            board[players_unit[0]][players_unit[1]] = board_road
            # vykresli hraca na novej pozicii
            board[next_position[0]][next_position[1]] = board_player[0]
            # nastavy jeho poziciu
            players_unit = next_position

        # vykresli hraciu plochu
        print_board(board)

        # ak je doma konci hra
        if is_home(players_unit) or (next_position is None and is_home(players_unit)):
            break


# tredia uloha, kompletna hra pre 1 az 4 hracov
def game():
    # hraci co vyhrali
    players_wins = []
    # vsetky jednotky na ploche
    players_units = [[],[],[],[]]
    # pozicie kde zacina hrac
    players_spawn_pos = [[half_board + 1, 0], [0, half_board - 1], [half_board - 1, board_size - 1], [board_size - 1, half_board + 1]]
    # spawn pre druheho hraca je na mieste tretieho ak hraju len dvaja
    if max_players == 2:
        players_spawn_pos[1]=players_spawn_pos[2]
    # pocet pripavenych panacikov
    spawn_count = [half_board - 2,half_board - 2,half_board - 2,half_board - 2]
    # pocet panacikov v domceku
    home_count = [0,0,0,0]
    # id hraca ktory je na tahu
    player_playing = 0
    # pocet aktulanych pokusom ak nema ziadneho panacika na hracej doske
    free_try = 0

    # vygeneruje krasnu plochu na hranie
    board = gen_board(board_size)

    # spawne kazdemu hracovy jedneho panacika
    for i in range(max_players):
        players_units[i].append([players_spawn_pos[i][0], players_spawn_pos[i][1]])
        draw_player(board,players_spawn_pos[i],i)

    # vykresli hraciu plochu
    print_board(board)

    # hlavny cyklus hry ak hraju este viac ako jeden
    while len(players_wins) < max_players - 1:
        # cakanie na tah a generovanie nahodneho cisla
        time.sleep(wait_time)
        rand = random.randint(1, 6)
        # vypis
        print("Hrac "+board_player[player_playing]+" hodil cislo "+str(rand))

        # ak hodil 6 a ma panacika na pridanie a uz tam nieje iny tak prida dalsieho
        if rand == 6 and spawn_count[player_playing] > 0 and check_move(players_units, players_spawn_pos[player_playing], player_playing) != 1:
            # odobere zo spawnu jedneho
            spawn_count[player_playing] = spawn_count[player_playing] - 1
            # prida do hry
            players_units[player_playing].append([players_spawn_pos[player_playing][0], players_spawn_pos[player_playing][1]])
            # vykresli
            draw_player(board,players_spawn_pos[player_playing],player_playing)

        # pokial nema ziadneho panacika tak moze hadzat 3x ak nehodi 6
        elif len(players_units[player_playing]) < 1:
            if rand != 6 and free_try < 2:
                free_try = free_try + 1
                continue

        # inak sa ide pohnut
        else:
            # najlepsia moznost pre pohyb
            move_unit = None
            next_position = None
            # priority na pohnutie, -1 = nic, 0 = pohyb v domceku, 1 = pohyb mimo domceka, 2 = vyhodenie hraca
            unit_priority = -1

            for unit in players_units[player_playing]:
                # aka bude dalsia pozicia pre panacika
                temp_next_position = next(unit,player_playing,rand)

                # ak sa nemoze pohnut skusi dalsieho
                if temp_next_position is None:
                    continue

                # skontroluje status policka kam sa ma pohnut, 0 = je volna cesta, 1 = ma tam vlastneho, 2 = ma tam nepriatela
                status = check_move(players_units,temp_next_position,player_playing)

                # ak ma moznost niekoho vyhodit
                if status == 2 and unit_priority < 2:
                    move_unit = unit
                    next_position = temp_next_position
                    unit_priority = 2

                # ak sa moze pohnut
                elif status == 0 and unit_priority < 1:
                    move_unit = unit
                    next_position = temp_next_position
                    unit_priority = 1

                # ak sa moze pohnut v domecku
                elif status == 0 and is_home(unit) and unit_priority < 0:
                    move_unit = unit
                    next_position = temp_next_position
                    unit_priority = 0

            # ak sa nasiel tak sa pohne
            if move_unit is not None:
                # nahradi hraca za cestu/domov podla toho kde stal
                board[move_unit[0]][move_unit[1]] = board_home if is_home(move_unit) else board_road
                # vykresli hraca na novej pozicii
                board[next_position[0]][next_position[1]] = board_player[player_playing]

                # ak ma vyhodit hraca tak ho aj vyhodi
                if unit_priority == 2:
                    remove_player(spawn_count,players_units,next_position)

                # ak nebol v domceku a uz je dostava hrac skore
                if not is_home(move_unit) and is_home(next_position):
                    home_count[player_playing] = home_count[player_playing] + 1
                    # ak uz ma plny domkec tak uz vyhral
                    if home_count[player_playing] > half_board - 2:
                        players_wins.append(player_playing)

                # nastavi novu poziciu
                move_unit[0] = next_position[0]
                move_unit[1] = next_position[1]

        # nakresli hraciu plochu
        print_board(board)

        # ak nehodil 6 tak uz ide dalsi hrac
        if rand != 6:
            free_try = 0
            player_playing = player_playing + 1 if player_playing < max_players - 1 else 0

    if len(players_wins) == 1:
        # ak hrali iba dvaja a je jeden vytaz vypise iba jedneho
        print("Hrac "+board_player[players_wins[0]]+" vyhral!")
    else:
        # ak hralo viac hracov vypise kazde miesto
        for i in range(len(players_wins)):
            print(str(i+1)+". miesto - hrac "+board_player[players_wins[i]])



# prva uloha
#if set_board_size():
#    board = gen_board(board_size)
#    print_board(board)

# druha uloha
#if set_board_size():
#    druha_uloha()

# tretia uloha
if set_board_size():
    game()

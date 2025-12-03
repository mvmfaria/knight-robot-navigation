import sys
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame

SQUARE_SIZE = 70
INPUT = "exemplo.txt"
OUTPUT = "solucao.txt"

KNIGHT = "imgs/knight.svg" 
KING = "imgs/king.svg"

WHITE = (240, 217, 181)
DARK = (181, 136, 99)
GRAY = (110, 105, 100)
PATH_COLOR = (34, 139, 34)

def load_input():
    data = {
        "obstacles": [],
        "dim": (8, 8),
        "target": (0,0),
        "start": (0,0)
    }

    with open(INPUT, 'r') as f:
        lines = f.readlines()
        h, w = map(int, lines[0].split())
        data["dim"] = (w, h)
        data["start"] = tuple(map(int, lines[1].split()))
        data["target"] = tuple(map(int, lines[2].split()))
        for line in lines[4:]:
            if line.strip():
                data["obstacles"].append(tuple(map(int, line.split())))
    return data

def read_solution():
    coordinates = []
    with open(OUTPUT, 'r') as f:
            for line in f:
                coordinates.append(tuple(map(int, line.split())))
    return coordinates

def load_image(filename, square_size):
    size = int(square_size * 0.9)
    size_tuple = (size, size)
    img_small = pygame.image.load(filename)
    img = pygame.transform.smoothscale(img_small, size_tuple)
    return img

input = load_input()
solution = read_solution()
COLUMNS, ROWS = input["dim"]

pygame.display.init()
pygame.font.init()
screen = pygame.display.set_mode((COLUMNS * SQUARE_SIZE, ROWS * SQUARE_SIZE))
pygame.display.set_caption(f"Total de movimentos: {len(solution) - 1}")

font_coord = pygame.font.SysFont("Arial", 12)

sprite_knight = load_image(KNIGHT, SQUARE_SIZE)
sprite_king = load_image(KING, SQUARE_SIZE)

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit(); sys.exit()

    for line in range(ROWS):
        for column in range(COLUMNS):
            color = WHITE if (line + column) % 2 == 0 else DARK
            rect = (column * SQUARE_SIZE, line * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE)
            pygame.draw.rect(screen, color, rect)
            lbl = font_coord.render(f"{column},{line}", True, (50,50,50))
            screen.blit(lbl, (column * SQUARE_SIZE + 2, line * SQUARE_SIZE + 2))

    for (x, y) in input["obstacles"]:
        rect = (x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE)
        
        pygame.draw.rect(screen, GRAY, rect)
        
        pygame.draw.rect(screen, (80, 75, 70), rect, 1) 

        lbl_obs = font_coord.render(f"{x},{y}", True, (255, 255, 255))
        screen.blit(lbl_obs, (x * SQUARE_SIZE + 3, y * SQUARE_SIZE + 3))

    if len(solution) > 1:
        dots = []
        for x, y in solution:
            px = x * SQUARE_SIZE + SQUARE_SIZE // 2
            py = y * SQUARE_SIZE + SQUARE_SIZE // 2
            dots.append((px, py))
        pygame.draw.lines(screen, PATH_COLOR, False, dots, 5)
        for p in dots: pygame.draw.circle(screen, PATH_COLOR, p, 6)

    tx, ty = input["target"]
    center_x = tx * SQUARE_SIZE + SQUARE_SIZE // 2
    center_y = ty * SQUARE_SIZE + SQUARE_SIZE // 2
    rect_king = sprite_king.get_rect(center=(center_x, center_y))
    screen.blit(sprite_king, rect_king)

    sx, sy = input["start"]
    center_x = sx * SQUARE_SIZE + SQUARE_SIZE // 2
    center_y = sy * SQUARE_SIZE + SQUARE_SIZE // 2
    rect_knight = sprite_knight.get_rect(center=(center_x, center_y))
    screen.blit(sprite_knight, rect_knight)

    pygame.display.flip()
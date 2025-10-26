#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DIGIT_WIDTH 10
#define DIGIT_HEIGHT 9

typedef struct {
    const char *rows[DIGIT_HEIGHT];
} Glyph;

static const Glyph DIGIT_GLYPHS[] = {
    {
        {
            "  ######  ",
            " ######## ",
            "###    ###",
            "###    ###",
            "###    ###",
            "###    ###",
            "###    ###",
            " ######## ",
            "  ######  "
        }
    },
    {
        {
            "    ##    ",
            "   ###    ",
            "  ####    ",
            " ## ##    ",
            "    ##    ",
            "    ##    ",
            "    ##    ",
            "    ##    ",
            " ######## "
        }
    },
    {
        {
            "  ######  ",
            " ######## ",
            "###    ###",
            "      ### ",
            "     ###  ",
            "   ###    ",
            " ###      ",
            "##########",
            "##########"
        }
    },
    {
        {
            "  ######  ",
            " ######## ",
            "###    ###",
            "      ### ",
            "   #####  ",
            "      ### ",
            "###    ###",
            " ######## ",
            "  ######  "
        }
    },
    {
        {
            "     ###  ",
            "    ####  ",
            "   #####  ",
            "  ## ###  ",
            " ##  ###  ",
            "##########",
            "##########",
            "      ### ",
            "      ### "
        }
    },
    {
        {
            "##########",
            "##########",
            "###       ",
            "########  ",
            "######### ",
            "      ### ",
            "###    ###",
            " ######## ",
            "  ######  "
        }
    },
    {
        {
            "   #####  ",
            "  ######  ",
            " ###      ",
            "########  ",
            "######### ",
            "###    ###",
            "###    ###",
            " ######## ",
            "  ######  "
        }
    },
    {
        {
            "##########",
            "##########",
            "      ### ",
            "     ###  ",
            "    ###   ",
            "   ###    ",
            "  ###     ",
            "  ###     ",
            "  ###     "
        }
    },
    {
        {
            "  ######  ",
            " ######## ",
            "###    ###",
            " ######## ",
            "  ######  ",
            " ######## ",
            "###    ###",
            " ######## ",
            "  ######  "
        }
    },
    {
        {
            "  ######  ",
            " ######## ",
            "###    ###",
            "###    ###",
            " #########",
            "  ########",
            "      ### ",
            " ######## ",
            "  ######  "
        }
    },
    {
        {
            "          ",
            "    ##    ",
            "    ##    ",
            "          ",
            "          ",
            "    ##    ",
            "    ##    ",
            "          ",
            "          "
        }
    }
};

static const Glyph *glyph_for_char(char c) {
    if (c >= '0' && c <= '9') {
        return &DIGIT_GLYPHS[c - '0'];
    }
    if (c == ':') {
        return &DIGIT_GLYPHS[10];
    }
    return NULL;
}

static void draw_clock(void) {
    time_t raw;
    struct tm *tm_info;
    char buffer[16];

    time(&raw);
    tm_info = localtime(&raw);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int len = (int)strlen(buffer);
    int total_width = len * DIGIT_WIDTH + (len - 1);
    int start_y = (max_y - DIGIT_HEIGHT) / 2;
    int start_x = (max_x - total_width) / 2;

    clear();

    if (max_y < DIGIT_HEIGHT + 2 || max_x < total_width + 2) {
        const char *msg = "Ampliar la ventana del terminal";
        mvaddstr(max_y / 2, (max_x - (int)strlen(msg)) / 2, msg);
        refresh();
        return;
    }

    for (int row = 0; row < DIGIT_HEIGHT; ++row) {
        for (int idx = 0; idx < len; ++idx) {
            const Glyph *glyph = glyph_for_char(buffer[idx]);
            if (!glyph) {
                continue;
            }
            int offset_x = start_x + idx * (DIGIT_WIDTH + 1);
            for (int col = 0; col < DIGIT_WIDTH; ++col) {
                char pixel = glyph->rows[row][col];
                mvaddch(start_y + row, offset_x + col, pixel);
            }
        }
    }

    refresh();
}

int main(void) {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);

    while (1) {
        draw_clock();
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        }
        usleep(100000);
    }

    endwin();
    return EXIT_SUCCESS;
}

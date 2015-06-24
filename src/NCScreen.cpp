#include "ncurses.h"
#include "NCScreen.h"
#include "NCRowMenu.h"
#include "NCPanelContainer.h"
#include "shared.h"
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <string>
#include "constants.h"
#include "Command.h"


NCScreen::NCScreen()
{
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	int COLOR_ROYAL = 19;
	int COLOR_BROWN = 10;
	int COLOR_GREY = 12;
	int COLOR_INACTIVE = 14;

	init_color(COLOR_ROYAL, 50,50,230);
	init_color(COLOR_BROWN, 400,400,100);
	init_color(COLOR_WHITE, 900,900,900);
	init_color(COLOR_BLACK, 0,0,0);
	init_color(COLOR_GREY, 200,200,200);
	init_color(COLOR_BLUE, 0, 0, 700);
	init_color(COLOR_RED, 700, 0, 0);
	init_color(COLOR_GREEN, 0, 700, 0);
	init_color(COLOR_INACTIVE, 500, 500, 500);

	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_GREY);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_RED, COLOR_GREY);
	init_pair(5, COLOR_INACTIVE, COLOR_GREY);

	bkgd(COLOR_PAIR(0));

	width = 0;
	height = 0;
    getmaxyx(stdscr, height, width);

    panels = new NCPanelContainer(height-3, 1, 2);
    panels->show();
    panels->changePanels();

    commandsMenu = new NCRowMenu(0, height-1, BottomMenu);
    commandsMenu->show();

    mainMenu = new NCRowMenu(0, 0, HeaderMenu);
    mainMenu->show();
}

void NCScreen::redrawAll()
{
	if (panels) panels->redraw();
	if (commandsMenu) commandsMenu->redraw();
	if (mainMenu) mainMenu->redraw();
	clearStatusBar();
	
	keypad(active_win, TRUE);
	update_panels();
	doupdate();
	wrefresh(active_win);
	redrawwin(active_win);
	refresh();
}

void subprocess(const std::string & cmd)
{
	pid_t pid = fork();

	if (pid == -1)
	{
	    exit(2);
	} 
	else if (pid > 0)
	{
	    int status;
	    waitpid(pid, &status, 0);
	}
	else
	{
		system(cmd.c_str());
	    exit(0);
	}
}

void NCScreen::clearStatusBar()
{
	for (int i = 0; i < width; i++)
		mvprintw(height-2, i, " ");

	mvprintw(height-2, 0, "cmd # ");
}

void NCScreen::loop()
{
	panels->changePanels();
	top_panel( activePanel->getPanel() );
	update_panels();
	doupdate();
	wrefresh(active_win);
	int ch;
	char name[100];
	
	redrawAll();

	width = 0;
	height = 0;
    getmaxyx(stdscr, height, width);

	while((ch = getch()) != KEY_F(10) && (ch != 'q'))
	{
		//std::cout << "selected: "<< item_name(current_item(active_menu)) << std::endl;
		std::string current = item_name(current_item(active_menu));
		std::string path = activePanel->getWidget()->getCurrentPath();
		std::string output;
		std::string tmp;
		name[0] = '\0';
		clearStatusBar();

		output.clear();
		tmp.clear();	

		Command cmd("");

		switch(ch)
		{
			case 9: // TAB
				panels->changePanels();
				top_panel( activePanel->getPanel() );
				update_panels();
				wrefresh(active_win);
				//doupdate();
				break;
			case KEY_DOWN:
				menu_driver(active_menu, REQ_DOWN_ITEM);
				wrefresh(active_win);
				break;
			case KEY_UP:
				menu_driver(active_menu, REQ_UP_ITEM);
				wrefresh(active_win);
				break;
			case KEY_LEFT:
				menu_driver(active_menu, REQ_LEFT_ITEM);
				wrefresh(active_win);
				break;
			case KEY_RIGHT:
				menu_driver(active_menu, REQ_RIGHT_ITEM);
				wrefresh(active_win);
				break;
			case ' ':
				menu_driver(active_menu, REQ_TOGGLE_ITEM);
				wrefresh(active_win);
				break;



			case KEY_F(1):

				cmd = Command(CMD_LESS);
				cmd.addArg(activePanel->getWidget()->getCurrentPath() + PATH_SEPARATOR + current);

				subprocess(cmd.getCommand());
				clearStatusBar();
				break;

			case KEY_F(2):

				cmd = Command(CMD_EDITOR);
				cmd.addArg(activePanel->getWidget()->getCurrentPath() + PATH_SEPARATOR + current);

				subprocess(cmd.getCommand());
				clearStatusBar();
				break;


			case KEY_F(3):
				cmd = Command(CMD_VIEW);
				cmd.addArg(activePanel->getWidget()->getCurrentPath() + PATH_SEPARATOR + current);
				cmd.addArg(" | ");
				cmd.addArg(CMD_LESS);

				subprocess(cmd.getCommand());
				clearStatusBar();
				break;

			case KEY_F(4):

				echo();

				mvprintw(height-2, 0, "Symlink name: ");
				getstr(name);

				cmd = Command(CMD_SYMLNK);
				cmd.addArg(path + PATH_SEPARATOR + current);
				cmd.addArg(panels->getNextPanelPath() + PATH_SEPARATOR + name);
				
				output = exec(cmd.getCommand(), true);
				if ( output == "" )
					output = "Symlink created.";

				mvprintw(height-2, 0, " > %s", output.c_str());
				noecho();

				panels->changePanels();
				activePanel->getWidget()->reload();
				panels->setActive(activePanel);
				top_panel( activePanel->getPanel() );
				break;



			case KEY_F(5):

				echo();

				mvprintw(height-2, 0, "Destination name: ");
				getstr(name);

				cmd = Command(CMD_CP);
				cmd.addArg(path + PATH_SEPARATOR + current);

				tmp = panels->getNextPanelPath() + PATH_SEPARATOR;
				if ( strlen(name) > 0 )
					tmp += name;
				else
					tmp += current;
				
				cmd.addArg(tmp);
				
				output = exec(cmd.getCommand(), true);
				if ( output == "" )
					output = "Copied.";

				mvprintw(height-2, 0, " > %s", output.c_str());
				noecho();

				activePanel->getWidget()->reload();
				panels->setActive(activePanel);
				top_panel( activePanel->getPanel() );

				panels->changePanels();

				activePanel->getWidget()->reload();
				panels->setActive(activePanel);
				top_panel( activePanel->getPanel() );
				break;


			case KEY_F(6):

				echo();

				mvprintw(height-2, 0, "Destination name: ");
				getstr(name);

				cmd = Command(CMD_MOVE);
				cmd.addArg(path + PATH_SEPARATOR + current);

				tmp = panels->getNextPanelPath() + PATH_SEPARATOR;
				if ( strlen(name) > 0 )
					tmp += name;
				else
					tmp += current;
				
				cmd.addArg(tmp);
				
				output = exec(cmd.getCommand(), true);
				if ( output == "" )
					output = "Moved.";

				mvprintw(height-2, 0, " > %s", output.c_str());
				noecho();

				activePanel->getWidget()->reload();
				panels->setActive(activePanel);
				top_panel( activePanel->getPanel() );

				panels->changePanels();

				activePanel->getWidget()->reload();
				panels->setActive(activePanel);
				top_panel( activePanel->getPanel() );
				break;

			case KEY_F(7):

				echo();

				mvprintw(height-2, 0, "New dirname: ");
				getstr(name);

				cmd = Command(CMD_MKDIR);
				cmd.addArg(activePanel->getWidget()->getCurrentPath() + PATH_SEPARATOR + name);

				output = exec(cmd.getCommand(), true);
				if ( output == "" )
					output = "Directory created.";

				mvprintw(height-2, 0, " > %s", output.c_str());
				noecho();

				activePanel->getWidget()->reload();
				panels->setActive(activePanel);
				
				break;

			case KEY_F(8):

				mvprintw(height-2, 0, "Are you sure? (y/N): ");
				ch = getch();

				if ( ch == 'y' )
				{
					cmd = Command(CMD_RM);
					cmd.addArg(path + PATH_SEPARATOR + current);

					output = exec(cmd.getCommand(), true);
					if ( output == "" )
						output = "Removed.";

					mvprintw(height-2, 0, " > %s", output.c_str());

					activePanel->getWidget()->reload();
					panels->setActive(activePanel);
				}
				
				break;


			case KEY_F(9):

				echo();

				mvprintw(height-2, 0, "New name: ");
				getstr(name);

				cmd = Command(CMD_RENAME);
				cmd.addArg(path + PATH_SEPARATOR + current);
				cmd.addArg(path + PATH_SEPARATOR + name);

				output = exec(cmd.getCommand(), true);
				if ( output == "" )
					output = "Renamed.";

				mvprintw(height-2, 0, " > %s", output.c_str());
				noecho();

				activePanel->getWidget()->reload();
				panels->setActive(activePanel);
				
				break;


			case 10: // ENTER

				if ( activePanel->getWidget()->isDir(current) || current == ".." )
				{
					activePanel->getWidget()->openDir(current);
					activePanel->setActive(true);
					panels->setActive(activePanel);
					top_panel( activePanel->getPanel() );
				}

				else
				{
				    cmd = Command(CMD_EDITOR);
					cmd.addArg(activePanel->getWidget()->getCurrentPath() + PATH_SEPARATOR + current);
					subprocess(cmd.getCommand());
				}
				break;
		}
		redrawAll();
	}
	endwin();
	system(CMD_CLEAR);
	
	std::cout << "Bye." << std::endl << "Lukas Kasic" << std::endl;
}



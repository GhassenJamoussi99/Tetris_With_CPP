#pragma once
#include "olcCOnsoleGameEngine.h"
#include <utility>
#include <fstream>
#include <string>
#include <codecvt>
#include <locale>
#include <windows.h>
#include <iostream>


class Tetris : public olcConsoleGameEngine
{
public:
	Tetris()
	{
		m_sAppName = L"Tetris";
	}
private:
	float fVelocity = 1.0f;
	int x_Bar = ScreenWidth() / 5 + 1;
	float y_Bar = 5.0f;
	int count = 0;
	//int pimp = 0;
	int count_bHasLanded1 = 0;
	int count_bHasLanded2 = 0;
	std::string arr_rand[5] = {"A","B","C","D"};
	std::wstring random = L"A";
	std::wstring arr_alph[4000];
	std::vector<std::pair< std::pair<int,int> , std::wstring> > xy1;
	std::vector<std::pair< std::pair<int,int> , std::wstring> > xy2;
	std::vector<std::pair<int, int>> store;
	std::wstring str1 = L" ";
	std::wstring str2 = L" ";
	bool cond = false;
	bool bLine = false;
	int  yLine = 0;
	int isGLine = 0;
	int count_line = 0;
	int max_line = 0;

	int test = 0;

	bool bHasLanded1 = false;
	bool bHasLanded2 = false;
	bool bHasLanded3 = false;
	bool bHasLanded4 = false;
	bool gameOver = false;
	bool toggle1 = false;
	bool toggle2 = false;
	bool bHasCollided = false;
	bool bResetGame = false;
	int up_released = 0;


protected:
	virtual bool OnUserCreate()
	{
		bResetGame = true;
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		std::ofstream Log;
		Log.open("Logfile.txt", std::ios_base::app); //For debugging

		if (bResetGame)
		{
			fVelocity = 1.0f;
			x_Bar = ScreenWidth() / 5 + 1;
			y_Bar = 5.0f;
			bHasCollided = false;
			bHasLanded1 = false;
			bHasLanded2 = false;
			bHasLanded3 = false;
			bHasLanded4 = false;
			bResetGame = false;
			gameOver = false;
			up_released = rand() % 4;
			bLine = false;
			count++;
		}
		if (gameOver)
		{
			DrawString(30, 4, L" Game over "); 
			DrawString(30, 5, L" Press Space to play again");

			if(m_keys[VK_SPACE].bPressed) // Or pressed ?
		    {
				//	Log << "test";
				xy1.clear();
				xy2.clear();
				bResetGame = true;
				gameOver = false;
				toggle1 = false;
				toggle2 = false;
				count_bHasLanded1 = 0;
				count_bHasLanded2 = 0;
				count_line = 0;
			}
			
		}


		if (bHasCollided)
		{
			bResetGame = true;
			random = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(arr_rand[rand() % 4]);
		}
		else
		{
			Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
			

			Fill(5, 5, 6, ScreenHeight() - 5, PIXEL_SOLID, FG_GREEN);                                                 //Vertical Line I
			Fill(5, ScreenHeight() - 5, (ScreenWidth() / 3) + 2, ScreenHeight() - 3, PIXEL_SOLID, FG_GREEN);          //Horizontal Line
			Fill(ScreenWidth() / 3 + 1, 5, (ScreenWidth() / 3) + 2, ScreenHeight() - 5, PIXEL_SOLID, FG_GREEN);       //Vertical Line II

			if (toggle1)
			{
				for (int i = 0; i < count_bHasLanded1; i++)
				{   
					DrawString(xy1[i].first.first, xy1[i].first.second, xy1[i].second); 
				}
			}

			if (toggle2)
			{
				for (int i = 0; i < count_bHasLanded2; i++)
				{
					DrawString(xy2[i].first.first, xy2[i].first.second, xy2[i].second);
				}
			}

			Fill(6, ScreenHeight() - 5, (ScreenWidth() / 3) + 2, ScreenHeight() - 5, PIXEL_SOLID, FG_RED);
			// Handle Input
			if (m_keys[VK_LEFT].bReleased)
			{
				if (up_released == 0 &&  m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar - 1].Char.UnicodeChar == L' ' && x_Bar != 5) //Vertical
					x_Bar -= 1.0;

				if (up_released == 1 && m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar - 1].Char.UnicodeChar == L' ' && x_Bar != 5) //Horizontal
					x_Bar -= 1.0;

				if (up_released == 2 && m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar - 1].Char.UnicodeChar == L' ' && x_Bar != 5) //Vertical
					x_Bar -= 1.0;

				if (up_released == 3 && m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar - 1].Char.UnicodeChar == L' ' && x_Bar != 5) //Horizontal
					x_Bar -= 1.0;
			}
			if (m_keys[VK_RIGHT].bReleased)
			{
				if (up_released == 0 && m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar + 2].Char.UnicodeChar == L' ' && x_Bar != 26  && !up_released && m_bufScreen[(int)(y_Bar + 2)*ScreenWidth() + x_Bar + 2].Char.UnicodeChar == L' ')
					x_Bar += 1.0;

				if (up_released == 1 && m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar + 2].Char.UnicodeChar == L' ' && x_Bar != 24)
					x_Bar += 1.0;

				if (up_released == 3 && m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar + 1].Char.UnicodeChar == L' ')
					x_Bar += 1.0;

				if (up_released == 2 && m_bufScreen[(int)(y_Bar)*ScreenWidth() + x_Bar + 2].Char.UnicodeChar == L' ' && x_Bar != 24)
					x_Bar += 1.0;
			}
			
			if (m_keys[VK_DOWN].bHeld && !gameOver)
			{
				y_Bar += 0.04;
			}
			else if (m_keys[VK_DOWN].bHeld && gameOver)
			{
				DrawString(30, 4, L" Game over "); //\nPress Space to play again");
				DrawString(30, 5, L" Press Space to play again");

			}

			// Collision Detection
			if (up_released == 0) // Vertical
			{
				bHasLanded1 = m_bufScreen[(int)(y_Bar + 3) * ScreenWidth() + x_Bar].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5 ||
				              m_bufScreen[(int)(y_Bar + 3) * ScreenWidth() + x_Bar + 1].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5;
			}
			else if ( up_released == 1)//Horizontal
			{
				bHasLanded2 = m_bufScreen[(int)(y_Bar + 1) * ScreenWidth() + x_Bar].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5 ||
					m_bufScreen[(int)(y_Bar + 1) * ScreenWidth() + x_Bar + 1].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5 ||
					m_bufScreen[(int)(y_Bar + 1) * ScreenWidth() + x_Bar + 2].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5 ||
					m_bufScreen[(int)(y_Bar + 2) * ScreenWidth() + x_Bar ].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5;
					 
			}
			else if (up_released == 2)//Horizontal
			{
				bHasLanded3 = m_bufScreen[(int)(y_Bar + 1) * ScreenWidth() + x_Bar].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5 ||
					m_bufScreen[(int)(y_Bar + 1) * ScreenWidth() + x_Bar + 2 ].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5 ||
					m_bufScreen[(int)(y_Bar + 2) * ScreenWidth() + x_Bar + 1 ].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5;

			}
			else if (up_released == 3)//Vertical with 4 points
			{
				bHasLanded4 = m_bufScreen[(int)(y_Bar + 4) * ScreenWidth() + x_Bar].Char.UnicodeChar != L' ' && x_Bar != 27 && x_Bar != 5;
			}

			if (m_keys[VK_UP].bPressed && up_released != 3)
			{ 
				up_released = rand() % 3;
			}

			if (!gameOver)
			{

				if (up_released == 0) //Vertical (up_released = false)
				{
					DrawString(x_Bar, y_Bar + 0, random);
					DrawString(x_Bar, y_Bar + 1, random);
					DrawString(x_Bar, y_Bar + 2, random);
					DrawString(x_Bar + 1, y_Bar + 2, random);
					if (y_Bar == 5 && bHasLanded1)
						gameOver = true;
					//Log << y_Bar << std::endl;


					if (bHasLanded1)
					{

						xy1.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar), random));
						xy1.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar + 1), random));
						xy1.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar + 2), random));
						xy1.push_back(std::make_pair(std::make_pair(x_Bar + 1, y_Bar + 2), random));
						//Log << x_Bar << " " << y_Bar << std::endl;
						count_bHasLanded1 += 4;
						toggle1 = true;
						bHasCollided = true;

					}
				}
				else if (up_released == 1)//Horizontal
				{
					DrawString(x_Bar + 0, y_Bar, random);
					DrawString(x_Bar + 0, y_Bar + 1, random);
					DrawString(x_Bar + 1, y_Bar, random);
					DrawString(x_Bar + 2, y_Bar, random);
					if (y_Bar == 5 && bHasLanded2)
						gameOver = true;
					//Log << y_Bar << std::endl;

					if (bHasLanded2)
					{

						xy2.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar + 1), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar + 1, y_Bar), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar + 2, y_Bar), random));

						count_bHasLanded2 += 4;
						toggle2 = true;
						bHasCollided = true;
					}
				}
				else if (up_released == 2)
				{
					DrawString(x_Bar + 0, y_Bar, random);
					DrawString(x_Bar + 1, y_Bar, random);
					DrawString(x_Bar + 1, y_Bar + 1, random);
					DrawString(x_Bar + 2, y_Bar, random);
					if (y_Bar == 5 && bHasLanded3)
						gameOver = true;
					//Log << y_Bar << std::endl;

					if (bHasLanded3)
					{

						xy2.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar + 1, y_Bar), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar + 1, y_Bar + 1), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar + 2, y_Bar), random));

						count_bHasLanded2 += 4;
						toggle2 = true;
						bHasCollided = true;
					}
				}
				else if (up_released == 3)
				{
					DrawString(x_Bar, y_Bar, random);
					DrawString(x_Bar, y_Bar + 1, random);
					DrawString(x_Bar, y_Bar + 2, random);
					DrawString(x_Bar, y_Bar + 3, random);
					if (y_Bar == 5 && bHasLanded4)
						gameOver = true;

					if (bHasLanded4)
					{

						xy2.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar + 1), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar + 2), random));
						xy2.push_back(std::make_pair(std::make_pair(x_Bar, y_Bar + 3), random));


						count_bHasLanded2 += 4;
						toggle2 = true;
						bHasCollided = true;
					}
				}
			}


			std::wstring first_str;
			int counter = 0;
			for (int y = 44; y > 5; y--)
			{ 
               
				for (int i = 0; i < count_bHasLanded1; i++)
				{
					if (xy1[i].first.second == y && xy1[i].second != L"")
					{
						isGLine++;
					}
				}

				for (int i = 0; i < count_bHasLanded2; i++)
				{
					if (xy2[i].first.second == y && xy2[i].second != L"") //first_str == xy2[i].second)
					{
						isGLine++;
					}
				}

				if (isGLine == 21)
				{
					bLine = true;
					//Log << "bLine" << bLine << std::endl;
					yLine = y;
					break;
				}

				isGLine = 0;
			}
		
			isGLine = 0;
			if (bLine)
			{
				count_line++;
				for (int i = 0; i < count_bHasLanded1; i++)
				{
					if (xy1[i].first.second == yLine)
					{
						xy1[i].second = L"";
					}
					else if (xy1[i].first.second < yLine)
					{
						xy1[i].first.second++;
					}
				}

				for (int i = 0; i < count_bHasLanded2; i++)
				{
					if (xy2[i].first.second == yLine)
					{
					   xy2[i].second = L"";
					}
					else if (xy2[i].first.second < yLine)
					{
						xy2[i].first.second++;
					}
				}
				bLine = false;
			}

			if (max_line < count_line)max_line = count_line;

			DrawString(40, 1, L" CurrentScore : " + std::to_wstring(count_line) +  L"  High Score : " + std::to_wstring(max_line));
			DrawString(40, 45, L" Created by G.J ©" );
				
			
			y_Bar += fVelocity * fElapsedTime;

		}
		return true;
	}
};

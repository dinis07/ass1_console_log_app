//File Name: Assignment_01_SPMA 
//Date: 20/11/17
//Author:D.A.Tavares	
//Description: Program to store note values, and duration. Converting values into MIDI and duration into seconds the programme is also able to beep the notes in the correct frequency.



#include <iostream>	
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <math.h>

std::vector<std::vector<std::string>> vecTrackNote;
std::vector<std::vector<int>> vecTrackMIDI;
std::vector<std::vector<int>> vecTrackMusicalDur;
std::vector <std::vector<float>> vecTrackDurSeconds;
std::vector<std::string> vecTrackName;
int bpm;

//Function	 :	Error Message.
//Arguments  :	No Arguments.
//Returns	 :	No Returns.
//Description:	Function is used to print error message which is used in all validation loops, and the error message
//				can be changed for all loops in this function.
void errorMsg()
{
	std::cout << "\n***************************ERROR***************************";
}

//Function	 :	Note Pitch Validation
//Arguments	 :	String called note, user enters string 'note'
//Returns	 :	Empty string if inserted note fails validation, and returns the note back it passes validation
//Description:	The function checks all characters of the string are in the correct format, or valid character types
//				to ensure the programme runs properly
std::string ValidateNotePitch(std::string note)
{
	if (islower(note[0]))
	{
		note[0] = toupper(note[0]);
	}
	if (note.length() != 2 && note.length() != 3)
	{
		errorMsg();
		std::cout << "\nThe note MUST be 2 or 3 characters long.\n";
		return "";
	}
	if (isalpha(note[0]) == false)	
	{
		errorMsg();
		std::cout << "\nFirst character MUST be a letter. \n";
		return "";
	}
	if ((int)note[0] < 65 || (int)note[0] > 71)	
	{											
		errorMsg();								
		std::cout << "\nFirst character MUST be letter 'A', 'B', 'C', 'D', 'E', 'F' or 'G'\n";
		return "";																			
	}
	if (note.length() == 3)																	
	{
		if (note[1] != '#')																						
		{																							
			errorMsg();																				
			std::cout << "\nThe second character needs to be a '#'\n";										
			return "";																						
		}
		if (note[0] == 'B' || note[0] == 'E')																
		{
			errorMsg();																								
			std::cout << std::endl << note[0] << "#" << note[2] << " does not exist in this programme!\n";			
			return "";																								
		}
	}
	if (isdigit(note[note.length() - 1]) == false)																	
	{																												
		errorMsg();																									
		std::cout << "\nThe last character must be a digit! \n";													
		return "";																									
	}
	else return note;																								
}

//Function	 :	Note Pitch to MIDI note Values
//Arguments	 :	String called note, user enters string 'note'
//Returns	 :	Retures the MIDI note of the note entered by the user
//Description:	The function maps the pitch note to numbers but analysing each character of the string, 
//				function is an integer because it returns an interger
int getMIDI(std::string note)
{
	int MIDInote;																										

	int MNotes[] = { 9, 11, 0, 2, 4, 5, 7 };																		



	for (int i = 65; i <= 71; i++)																					
	{																												
		if ((int)note[0] == i)																						
		{
			MIDInote = MNotes[i - 65];																				
		}																											
	}
	if (note[1] == '#')																								
	{
		MIDInote = MIDInote + 1;																					
	}

	for (int i = 48; i <= 57; i++)																					
	{

		if ((int)note[(note.length() - 1)] == i)																	
		{
			MIDInote = MIDInote + ((i - 48) * 12);																	
		}
	}
	return MIDInote;																								
}

//Function	 :	Validate note duration
//Arguments	 :	int 'noteDur' entered by user
//Returns	 :	boolean value, true or false.
//Description:	The function validates the musical duration entered by the user 	
bool valDur(int noteDur)
{
	int mDur[] = { 1, 2, 4, 8, 16, 32 };																				

	for (int i = 0; i < 6; i++)																							
	{
		while (noteDur == mDur[i])																						
		{
			return true;																								
		}
	}

	return false;
}

//Function	 :	Insert note values
//Arguments	 :	int numTracks
//Returns	 :	no return, void.
//Description:	The function recieves the track names, amount of notes in each track duration for each note,
//				calls notes and duration for validation
void InsertNote(int numTracks)
{
	std::string trackName;																									
	std::string note;																										
	std::string snumNotes;																									
	std::string snoteDur;																									
	int noteDur;																											
	int numNotes;																											
	int MIDInote;																											

	for (int i = 0; i < numTracks; i++)																					
	{
		std::cout << "\nTrack " << i + 1 << " Input" << std::endl;														
		std::cout << "-------------\n";																					

		std::cout << "Enter name for track without any spaces\n";														
		std::cout << "Track " << i + 1 << ": ";																			
		std::cin >> trackName;																							
		std::cin.ignore(trackName[trackName.length() - 1], '\n');														

		vecTrackName.push_back(trackName);																				

		std::cout << "\n\n" << vecTrackName[i] << " Note Input \n";														

		for (int e = 0; e <= vecTrackName[i].length() + 11; e++)														
		{
			std::cout << "-";
		}

		std::cout << "\nHow many notes would you like to use for " << vecTrackName[i] << ": ";							
		std::cin >> snumNotes;																							

		while (true)																									
		{
			for (int y = 0; y < snumNotes.length(); y++)																
			{
				while (isdigit(snumNotes[y]) == false)																	
				{
					errorMsg();																							
					std::cout << "\nValue must be a digit\n";															
					std::cout << "Insert number of notes for " << vecTrackName[i] << ": ";
					std::cin >> snumNotes;																					
			}
			numNotes = std::stoi(snumNotes);																			
			break;																										
		}

		std::vector<std::string> vecNote;															
		std::vector<int> vecMIDI;																	
		std::vector<int>vecDur;																		
		std::vector<float>vecDurSeconds;															

		for (int j = 0; j < numNotes; j++)
		{
			if (numNotes > vecNote.size())															
			{
				std::cout << "\nPlease insert a note in 'Note-Octave' format (eg. a#2, c4, F#7)\n";

				for (int k = 0; k < numNotes; k++)													
				{
					std::cout << "Insert note " << k + 1 << ": ";
					std::cin >> note;

					note = ValidateNotePitch(note);													

					while (note.empty())															
					{
						std::cout << "Enter " << vecTrackName[i] << " note " << k + 1 << " again: ";
						std::cin >> note;

						note = ValidateNotePitch(note);												
					}
					vecNote.push_back(note);														
					MIDInote = getMIDI(note);														
					vecMIDI.push_back(MIDInote);													
				}
				vecTrackNote.push_back(vecNote);													
				vecTrackMIDI.push_back(vecMIDI);													
			}
		}

		std::cout << "\nPlease enter note duration for " << vecTrackName[i] << "  (e.g. 1/1, 1/2, 1/4, 1/8, 1/16, 1/32). \n";

		for (int w = 0; w < numNotes; w++)															
		{
			std::cout << "Insert " << vecNote[w] << " Duration: 1/";
			std::cin >> snoteDur;

			while (true)
			{
				for (int l = 0; l < snoteDur.length(); l++)											
				{
					if (isdigit(snoteDur[l]) == false)												
					{
						errorMsg();
						std::cin.clear();															
						std::cin.ignore(256, '\n');													
						std::cout << "\nValue must be a digit\n";
						std::cout << "Insert " << vecNote[w] << " Duration: 1/";
						std::cin >> snoteDur;														
					}
				}

				noteDur = std::stoi(snoteDur);														
				break;																				
			}

			while (valDur(noteDur) == false)														
			{
				errorMsg();
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cout << "\nPlease only enter a duration of 1/1, 1/2, 1/4, 1/8, 1/16 or 1/32\n";
				std::cout << "Insert " << vecNote[w] << " Duration: 1/";
				std::cin >> noteDur;																
			}

			vecDur.push_back(noteDur);																

			float secDur = 60000 / bpm * 4;															
			secDur = secDur / 1000;																	
			secDur = secDur / noteDur;																

			vecDurSeconds.push_back(secDur);														
		}
		vecTrackMusicalDur.push_back(vecDur);														
		vecTrackDurSeconds.push_back(vecDurSeconds);												
	}
}

int main()
{
	std::string trackName;
	std::string note;

	std::string sbpm;
	std::string snumTracks;

	int numTracks;

	std::cout << "Please enter the project tempo in BPM (between 20 & 300): ";
	std::cin >> sbpm;

	for (int i = 0; i < sbpm.length(); i++)
	{
		while (true)
		{
			if (sbpm.length() != 2 && sbpm.length() != 3)
			{
				errorMsg();
				std::cout << "\nEnter a value between 20 and 300\n";
				std::cout << "Insert project tempo: ";
				std::cin >> sbpm;
			}
			if (isdigit(sbpm[i]) == false)
			{
				errorMsg();
				std::cout << "\nValue must be a digit\n ";
				std::cout << "Insert project tempo: ";
				std::cin >> sbpm;
			}
			bpm = std::stoi(sbpm);
			if (bpm < 20 || bpm > 300)
			{
				errorMsg();
				std::cout << "Enter a value between 20 and 300\n";
				std::cout << "Insert project tempo: ";
				std::cin >> sbpm;
			}
			else break;
		}
	}

	std::cout << "\nHow many tracks would you like to use: ";
	std::cin >> snumTracks;

	while (true)
	{
		for (int i = 0; i < snumTracks.length(); i++)
		{
			while (isdigit(snumTracks[i]) == false)
			{
				errorMsg();
				std::cout << "\nValue must be a digit\n";
				std::cout << "Insert number of tracks: ";
				std::cin >> snumTracks;
			}
		}

		numTracks = std::stoi(snumTracks);
		break;
	}

	double freq;																														
	double playDur;																														

	InsertNote(numTracks);

	std::cout << "\n\n*-------------------------------RESULTS-------------------------------*\n\n";

	std::cout << "Project BPM: " << bpm << std::endl;

	for (int i = 0; i < vecTrackNote.size(); i++)
	{

		std::cout << std::endl << vecTrackName[i] << " " << std::endl;

		for (int e = 0; e < vecTrackName[i].length(); e++)
		{
			std::cout << "-";
		}

		std::cout << std::endl;

		//std::cout << vecTrackNotes[i][ << "Notes: " 

		for (int j = 0; j < vecTrackNote[i].size(); j++)
		{
			std::cout << j + 1 << ") " << "Name: " << vecTrackNote[i][j] << " MIDI: " << vecTrackMIDI[i][j] << " Duration: 1/" << vecTrackMusicalDur[i][j];  
			std::cout << std::fixed << std::setprecision(3) << " (" << vecTrackDurSeconds[i][j] << " seconds)";

			playDur = vecTrackDurSeconds[i][j] * 1000;

			freq = vecTrackMIDI[i][j] - 57;
			freq = freq / 12;
			freq = 440 * pow(2, freq);

			std::cout << ", Freq: " << freq << " hz " << std::endl;

			Beep(freq, playDur);																											
		}
	}

	std::cout << "\n			*END OF PROGRAMME*		\n" << std::endl;

	return 0;
}


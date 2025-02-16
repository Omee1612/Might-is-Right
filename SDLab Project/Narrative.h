#ifndef NARRATIVE_H
#define NARRATIVE_H

#include <map>
#include <memory>
#include <vector>
#include <string>

#include "Entity.h"

class Narrative
{
public:
	// Character Images
	int omeeImage;
	int aiyanImage;
	int tirthoImage;
	int raziImage;
	// Multiple narratives storage
	std::vector<std::map<int, std::vector<std::string>>> narratives;
	std::vector<std::vector<int>> speakerOrders;
	int activeNarrativeIndex; // Current active narrative
	int currentSpeakerIndex;
	int dialogueIndex;
	// UI Elements
	int speechBox;
	int textPosX;
	int textPosY;
	// Narrative State
	bool narrativeActive;
	// Constructor
	Narrative()
	{
		textPosX = 150;
		textPosY = 100;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		activeNarrativeIndex = -1;
		narrativeActive = false;
		loadImages();
	}
	// Load character images
	void loadImages()
	{
		omeeImage = iLoadImage("res/narrative/p1head.png");
		aiyanImage = iLoadImage("res/narrative/p2head.png");
		tirthoImage = iLoadImage("res/narrative/p3head.png");
		raziImage = iLoadImage("res/narrative/p4head.png");
		speechBox = iLoadImage("res/narrative/speechBox.png");
	}
	// Start a specific narrative sequence
	void startNarrative(int index)
	{
		if (index < 0 || index >= narratives.size())
			return;

		activeNarrativeIndex = index;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	// Render dialogue box and text
	void renderDialogue()
	{
		if (!narrativeActive || activeNarrativeIndex == -1) return;

		auto& activeDialogues = narratives[activeNarrativeIndex];
		auto& activeSpeakers = speakerOrders[activeNarrativeIndex];

		if (currentSpeakerIndex >= activeSpeakers.size()) return;

		int speaker = activeSpeakers[currentSpeakerIndex];

		// Draw speech box first
		iShowImage(0, 10, 1920, 120 * 1.8, speechBox);

		// Draw character portrait
		iShowImage(10, 50, 128 * 2.4, 128 * 1.8, speaker);

		// Set text color (Make sure it's visible)
		iSetColor(255, 255, 255); // White text for contrast

		// Display text AFTER images
		std::string text = activeDialogues[speaker][dialogueIndex];
		iText(textPosX * 2.4, textPosY * 1.8, const_cast<char*>(text.c_str()), GLUT_BITMAP_HELVETICA_18);
	}
	void loadLevel1Narrative()
	{
		std::map<int, std::vector<std::string>> level1Dialogue = {
			{ omeeImage, { "koi aya porsi" } },
			{ aiyanImage, { "tui janos ki game banas hala" } },
			{ tirthoImage, { "e bai amar bonduk eto sodo ken" } },
			{ raziImage, { "relax you all" } }
		};

		std::vector<int> level1Speakers = { omeeImage, aiyanImage, tirthoImage, raziImage };

		narratives.push_back(level1Dialogue);
		speakerOrders.push_back(level1Speakers);

		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel1Narrative2()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ raziImage, { "Whot tha hell this is v ery tuff." } },
			{ aiyanImage, { "e hala ei konkal edi ailo koitte mama" } },
			{ tirthoImage, { "chop eto kisu jana lagbo ken ekhon khali pita" } }
		};

		std::vector<int> levelSpeakers = { raziImage, aiyanImage, tirthoImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel1Narrative3()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ tirthoImage, { "e hala ei nega ailo koitte" } },
			{ aiyanImage, { "mama bornobad korisna project dekhaite parum na sir re" } },
			{ raziImage, { "Yes yes we shood all b respectful to every1" } },
			{ omeeImage, { "bhor kalua re" } }
		};

		std::vector<int> levelSpeakers = { tirthoImage, aiyanImage, raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel1Narrative4()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ tirthoImage, { "nega halay morse" } },
			{ omeeImage, { "bhai kaula da kemon chaai hoye gelo" } },
			{ raziImage, { "god damn this is sO krezy" } },
			{ aiyanImage, { "razi emne kotha koy ken" } }
		};

		std::vector<int> levelSpeakers = { tirthoImage, omeeImage, raziImage, aiyanImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel2Narrative1()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ omeeImage, { "kire jahangirnagar choila ailam koitte" } },
			{ tirthoImage, { "e beyadob muk shamlay kotha ko amar girlfren jahangirnagar pore" } },
			{ raziImage, { "my mans this place is so skery" } },
			{ aiyanImage, { "mama amare to mosha kamray" } }
		};

		std::vector<int> levelSpeakers = { omeeImage, tirthoImage, raziImage, aiyanImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel2Narrative2()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ aiyanImage, { "mama amare ekhono mosha kamray dengue hoibo to" } },
			{ tirthoImage, { "dhur tor moshar gushti eidik bhutni gula amgore kilaitese" } }
		};

		std::vector<int> levelSpeakers = { aiyanImage, tirthoImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel2Narrative3()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ aiyanImage, { "e bai ei daa boti niye ke aise" } },
			{ tirthoImage, { "magoma kolla kati dibe" } },
			{ raziImage, { "it is all right frendz i am sure we can reason with this person" } },
			{ omeeImage, { "reason korte gele tomar lulli kaite dibe bhodai" } }
		};
		std::vector<int> levelSpeakers = { aiyanImage, tirthoImage , raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel2Narrative4()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ aiyanImage, { "mama icecream goilla gelo" } },
			{ tirthoImage, { "kha tui oidi boya" } },
			{ raziImage, { "can we please get outof here the mosquitos are killing me" } },
			{ omeeImage, { "tui ingrezi kowa bondho kor bangal" } }
		};
		std::vector<int> levelSpeakers = { aiyanImage, tirthoImage, raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	// Advance dialogue
	void nextDialogue()
	{
		if (!narrativeActive || activeNarrativeIndex == -1) return;

		auto& activeDialogues = narratives[activeNarrativeIndex];
		auto& activeSpeakers = speakerOrders[activeNarrativeIndex];

		if (currentSpeakerIndex >= activeSpeakers.size()) return;

		int speaker = activeSpeakers[currentSpeakerIndex];

		if (dialogueIndex < activeDialogues[speaker].size() - 1)
		{
			// Move to next dialogue of the same speaker
			dialogueIndex++;
		}
		else
		{
			// Move to next speaker
			dialogueIndex = 0;
			currentSpeakerIndex++;

			// End narrative if all dialogues are finished
			if (currentSpeakerIndex >= activeSpeakers.size())
			{
				narrativeActive = false;
			}
		}
	}
};
#endif // NARRATIVE_H

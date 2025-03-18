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
			{ raziImage, { "it is all right frendz we can reason with this person" } },
			{ omeeImage, { "aise british reason maraite" } }
		};
		std::vector<int> levelSpeakers = { aiyanImage, tirthoImage, raziImage, omeeImage };
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
			{ aiyanImage, { "mama oi to chaai hoya gelo" } },
			{ tirthoImage, { "bro is cooked fr" } },
			{ raziImage, { "whot do you mean we are not cooking anything" } },
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
	void loadLevel3Narrative1()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ tirthoImage, { "background ta to shei chobi bhalo uthbo eikhane" } },
			{ aiyanImage, { "ho iphone ta bair kor" } },
			{ raziImage, { "but we do not have any camera stupid" } },
			{ omeeImage, { "age shamne pise ki aise dekh bhodai" } }
		};
		std::vector<int> levelSpeakers = { tirthoImage, aiyanImage, raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel3Narrative2()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ tirthoImage, { "edi to bohut genjaimma" } },
			{ aiyanImage, { "e bhai dekh kotogula borka pore ki martese" } },
			{ raziImage, { "we shall not let any sorcery hinder us!" } },
		};
		std::vector<int> levelSpeakers = { tirthoImage, aiyanImage, raziImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel3Narrative3()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ omeeImage, { "khaise re eibar 2 da ekloge?" } },
			{ aiyanImage, { "ajkei hoyto shesh polok felte hobe" } },
			{ raziImage, { "mama age uronto bhodai tare dhor naile morum ekdom sure" } },
			{ tirthoImage, { "razi bangla koite pare? " } }
		};
		std::vector<int> levelSpeakers = { omeeImage, aiyanImage, raziImage, tirthoImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel3Narrative4()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ tirthoImage, { "na mama bohut koshto hoilo amare chara tora ki korti" } },
			{ aiyanImage, { "amare chara ki korti oiti ko bolod" } },
			{ raziImage, { "pls all maintain decorum" } },
			{ omeeImage, { "ei ingrez halay abar decoration maray" } }
		};
		std::vector<int> levelSpeakers = { tirthoImage, aiyanImage, raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel4Narrative1()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ tirthoImage, { "mamo castle te ber hoite na hoitei dehi abar genjam" } },
			{ aiyanImage, { "mama edire na age mere ashsi je game banaise tar mone hoy creativity eitukei shesh" } },
			{ raziImage, { "u r absolutely right this is boring & repetitive" } },
			{ omeeImage, { "*** ******** **** *** ******* ** " } }
		};
		std::vector<int> levelSpeakers = { tirthoImage, aiyanImage, raziImage, omeeImage, raziImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel4Narrative2()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ tirthoImage, { "kire eitareo to pitaisilam" } },
			{ aiyanImage, { "negative review dimu faltu" } },
			{ raziImage, { "i agree this game also lacks diversity & inclusivity there are no bla-" } },
			{ omeeImage, { "thabor dibo" } },
		};
		std::vector<int> levelSpeakers = { tirthoImage, aiyanImage, raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel4Narrative3()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ aiyanImage, { "bai last level manei ki shob boss ekloge diya dibi" } },
			{ tirthoImage, { "pera koi mojai to lagtese" } },
			{ raziImage, { "we are like anime protagonists who have went through their training arc and have become stronger" } },
			{ omeeImage, { "aise salikin 2.0" } },
		};
		std::vector<int> levelSpeakers = { aiyanImage, tirthoImage, raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLevel4Narrative4()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ aiyanImage, { "mama eiti ki final boss" } },
			{ tirthoImage, { "bhab shab to omoni" } },
			{ raziImage, { "do not worry frends we will slay him like all the others" } },
			{ omeeImage, { "shobar age tore pidai" } },
		};
		std::vector<int> levelSpeakers = { aiyanImage, tirthoImage, raziImage, omeeImage };
		narratives.push_back(levelDialogue);
		speakerOrders.push_back(levelSpeakers);
		activeNarrativeIndex = narratives.size() - 1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = true;
	}
	void loadLastNarrative()
	{
		std::map<int, std::vector<std::string>> levelDialogue = {
			{ aiyanImage, { "mama amra ki jitsi" } },
			{ tirthoImage, { "ho mama amgo course shesh" } },
			{ raziImage, { "chokh diye pani portice" } },
			{ omeeImage, { "ei halay ekhon abar bangla koy ere group theke bair kor" } },
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
	void reset()
	{
		activeNarrativeIndex = -1;
		currentSpeakerIndex = 0;
		dialogueIndex = 0;
		narrativeActive = false;
		narratives.clear();
		speakerOrders.clear();
	}
};
#endif // NARRATIVE_H

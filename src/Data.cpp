#include "Data.h"
#include <string>
#include <vector>
using namespace std;


Entry entries[] = {

	Entry("Intro1", "#p4#cWInstructions:#cD#n #p3Press and hold #cWSPACEBAR#cD#p1 to increase the speed of the text.#n #p4To make a choice#p2, press the #cWnumeric key#cD#p1 that corresponds to the #cWpurple option#cD.#p3")
	.AddOptions(
		Option("Got it!", "Intro2")
	),

	Entry("Intro2", "They took my #cWbadge#cD#p3#n They took my #cWgun#cD#p3#n They took my #cWdignity#cD#p3#n They took my #cWdaughter#cD#p3#n #p1#n But I will take it all back#p3#n ...and I will have my #cR#s0#e1VENGEANCE#cD#p3 #n #n #n #n #n #s0a game made in #cW48 hours#cD for #cWLudum Dare 45#cD by #cWTommy Salomonsson#p2#cD#n Theme: #cWStart With Nothing#cD")
	.AddOptions(
		Option("Get vengeance!", "StartGame")
	),

	Entry("StartGame", "It’s a mess!#p2 Broken furniture everywhere. All drawers has been emptied and the floor is covered with broken glass, ruined books and... #cRis that blood?#cD#p3#n #n The phone rings. It’s #cWsharp signal piercing my brain#cD.#p2 They tell my #cRthey have my daughter#cD.#p2 They say they will #s4#cRkill her in 10 hours#cD#s1 then they hang up. No demands. Nothing else. My head hurts but I pull myself together.#n #n Something bigger is happening here. I am #cWfalsely accused and suspended#cD from the force#p1 at the same time as #cWmy daughter is kidnapped#cD.#p3 #cRBut they chose the wrong person to mess around with!#cD")
	.AddOptions(
		Option("Continue", "Apartment1")
	),

	Entry("Apartment1", "My apartment looks like a crime scene. I should probably report it to the police, but I don’t trust those spineless maggots,#p3 hiding behind their desks.")
	.AddText(
		OptionalText("#n #n Maybe Martin could help though. He’s a tough motherfucker.").HideIfKey(GameKey::CalledMartin))
	.AddOptions(
		Option("Call Martin", "CallMartin").HideIfKey(GameKey::CalledMartin).TriggerKey(GameKey::CalledMartin),
		Option("I need to get my gun back", "GetGun1"),
		Option("I need to get my badge back", "GetBadge1"),
		Option("I need to get my dignity back", "GetDignity1"),
		Option("I need to get my daughter back", "GetDaughter1")
	),

	Entry("CallMartin", "It takes me several phone calls before I get the answers I need.#n #n Martin is away on a #cWblack ops mission again#cD. Probably #cWIraq or Syria#cD. #cR#s2He won’t be back for at least 6 months.#cD#s1 It means I have to take care of this on my own.")
	.AddOptions(
		Option("Continue", "Apartment1")
	),

	Entry("Apartment2", "").TriggerKey(GameKey::HasFriend)
	.AddText(
		OptionalText("Back in the apartment again.#n #n In the middle of the chaos stands #cGMartin#cD. He must have come home earlier from his mission.#n #n Anyone who has met Martin knows that he is nothing short of a demon! #p2With his broad smile that never reaches his eyes.And with killing efficiency whatever he puts his mind to!#n #n “I heard you were in trouble” he says, still with that smile. “I thought you needed some help!”#n #n Outside the sun is setting.")
		.HideIfKey(GameKey::HasFriend))
	.AddText(
		OptionalText("The apartment is in a sorry state. But not in such a sorry state as the bastards who blew me over!")
		.ShowIfKey(GameKey::HasFriend))
	.AddOptions(
		Option("I need to get my gun back", "GetGun1").HideIfKey(GameKey::HasGun),
		Option("I need to get my badge back", "GetBadge1").HideIfKey(GameKey::HasBadge),
		Option("I need to get my dignity back", "GetDignity1"),
		Option("I need to get my daughter back", "GetDaughter1")
	),
	

	Entry("GetGun1", "I’ve been on the force for ten years. The gun is a part of me. I’m naked without it.#n #n I do have a spare gun. But Sofia made me promise never to use it, so I dug it down in the garden. It’s in a box so it should still be working. I did promise her however…#n #n Also there’s Lazlo.That shithead, petty crime lord, who somehow seems to be untouchable by the law. I’ve crossed him a couple of times, and he can be intimidated into giving me a weapon.")
	.AddOptions(
		Option("Dig up the gun in the garden (soul -1, ammo +1)", "Garden").TriggerKey(GameKey::HasGun),
		Option("Visit Lazlo", "Lazlo"),
		Option("Nevermind, I’ll get by without a gun", "Apartment1").HideIfKey(GameKey::HasFriend),
		Option("Nevermind, I’ll get by without a gun", "Apartment2").ShowIfKey(GameKey::HasFriend)
	),

	Entry("Garden", "The mist is thick outside, making it hard to see more than a few meters. The vague shapes of the trees around me look like deformed bodies watching me. In the distance I hear someone crying. The sound is driving me nuts.#n #n I dig up the wooden box and open it.The revolver is in it. And a single bullet#e5. I feel ashamed as I take them, I promised Sofia!#e3 But now she’s gone, and she needs me. I might need more than a single bullet though...")
	.AddOptions(
		Option("Investigate the crying sound (soul -1)", "Neighbour"),
		Option("Maybe I should visit Lazlo anyway", "Lazlo"),
		Option("One bullet will be enough", "Apartment2")
	),

	Entry("Neighbour", "The crying sound seems to come from my neighbour. She is standing in the lawn, hunched over something. Another hysterical woman, just what I need... The wet, thick mist makes it hard to see. I move closer. She looks smaller...#n #n She looks up.“You took the gun!You promised you would never take the gun!”#e3. #cRThe dog in her lap is growling at me.#cD")
	.AddOptions(
		Option("Shoot the dog (ammo -1)", "Neighbour2").ShowIfKey(GameKey::HasAmmo),
		Option("Run away", "Apartment2")
	),

	Entry("Neighbour2", "#s0#cRBang!#e2#n #n That dog was going to attack! I had no choice! She keeps on crying.#n #n But I’m out of bullets. I should either pay Lazlo a visit, or just keep going without a weapon.")
	.AddOptions(
		Option("Visit Lazlo", "Lazlo"),
		Option("Go back inside", "Apartment2")
	),


	Entry("Lazlo", "I manage to arrange a meeting with Lazlo.#p3 We’ve met a couple of times and scratched each others backs. But he is a slippery bastard!#p2 His #cRhuge dog#cD lying by his feet, black eyes watching me.#p3 His raspy voice tears through the fog.#n #n “So now it suits you to beg for favours#p2, you piece of shit!#p3 I heard you were kicked out of the force!#p2 Actually... I hear all kind of things about you lately!”#p3#n #n That son of a bitch. I’ve had his back more times than I can count, but he thinks he can treat me like this?#p2 I would kick his ass if it wasn’t for that huge-ass dog of his.#p2#n #n “Tell me what, I’ll help you out if you do me a small favour!”#p2#n #n (If I could flash my badge it would shut his smirky face)")
	.AddOptions(
		Option("What favour?", "LazloSoul1"),
		Option("Attack him and take what I need (ammo -1 and health -1)", "LazloShoot1").ShowIfKey(GameKey::HasAmmo),
		Option("Attack him and take what I need (health -3)", "LazloAtkUnarmed1").HideIfKey(GameKey::HasAmmo),
		Option("Show him the badge", "LazloBadge1").ShowIfKey(GameKey::HasBadge)
	),

	Entry("LazloSoul1", "He smirks at me#p2, showing a fine line of white teeth.#p3#n #n “Just give me #cRa piece of your soul!#cD” he says...")
	.AddOptions(
		Option("Give him what he wants (soul -1 ammo +3)", "Apartment2").TriggerTrigger(GameTrigger::AddAmmo3SoulMinus1),
		Option("Or attack him and take what I need (ammo -1 and health -1)", "LazloShoot1").ShowIfKey(GameKey::HasAmmo),
		Option("Or attack him and take what I need (health -3)", "LazloAtkUnarmed1").HideIfKey(GameKey::HasAmmo)
	),

	Entry("LazloAtkUnarmed1", "#e1#p3I hit him right in the face!#p3#n #n He tumbles and falls.#p2#n #n #cRThe dog is on me in an instant.#cD")
	.AddOptions(
		Option("Continue", "LazloAtkUnarmed2")
	),

	Entry("LazloAtkUnarmed2", "The dog bites!#e4#e4#e4#p2 Sharp teeth penetrating my skin!")
	.AddOptions(
		Option("Continue", "LazloAtkUnarmed3").TriggerKey(GameKey::HasGun)
	),

	Entry("LazloAtkUnarmed3", "#e6I cannot remember how I got away.#p2 It hurts like hell! But I have the gun#p2, and somehow I managed to get #cR3 more bullets#cD.#p3 They will come in handy!")
	.AddOptions(
		Option("Continue", "Apartment2")
	),

	Entry("LazloShoot1", "He stands there laughing, but he stops instantly the moment I pull out my gun.")
	.AddOptions(
		Option("Shoot the dog (ammo -1)", "LazloShootDog1"),
		Option("Shoot Lazlo (ammo -1)", "LazloShoot2")
	),

	Entry("LazloShootDog1", "#e2#s0#cRBANG#cD#s1#p3 The dog is out! Just Lazlo to deal with!#p3 He screams and takes a swing at me.")
	.AddOptions(
		Option("Continue", "LazloShootDog2")
	),

	Entry("LazloShootDog2", "#e4#p3 His fist hits my face!")
	.AddOptions(
		Option("He’ll regret that!", "LazloShootDog3")
	),

	Entry("LazloShootDog3", "I punch him in the stomach and he goes down.#p3#n #n Not so cocky anymore.#n #nI go over his pockets and finds #cRa gun and 6 bullets#e7.#cD")
	.AddOptions(
		Option("Take it", "Apartment2")
	),

	Entry("LazloShoot2", "#e2#cR#s0BANG#cD#s1#p3 Lazlo falls down, a hole between his eyes.#p2 But that huge dog is on me in an instant! ")
	.AddOptions(
		Option("Continue", "LazloAtkUnarmed2")
	),

	Entry("LazloBadge", "I show him the badge and his smile goes away.#p1 He looks suspiciously at me.#n #n “All right! Fine!”#p1 he says and tosses me a handgun. #p2Loaded with 6 bullets.#p2 “Get out of here you piece of shit”.")
	.AddOptions(
		Option("Lets get back home", "Apartment2")
	),

	Entry("GetBadge1", "I have no choice, I need my badge back. I need to go back to my old boss and tell her how incredibly sorry I am, and beg her to take me back.#n #n It’s crazy. #s2It is THEY who should beg ME to come back.#s1 I always did what was needed. I never complained. I had great results.")
	.AddOptions(
		Option("Lets visit the police station", "GetBadge3"),
		Option("Do it later", "Apartment1").HideIfKey(GameKey::HasFriend),
		Option("Do it later", "Apartment2").ShowIfKey(GameKey::HasFriend)
	),

	Entry("GetBadge3", "I walk slowly up to her office. I see all the officers behind their desks staring at me as I pass them. Spineless maggots!")
	.AddText(
		OptionalText("#p2#n #n Feeling the cold steele of my gun inside the pocket of my jacket makes me a bit calmer.").ShowIfKey(GameKey::HasAmmo))
	.AddText(
		OptionalText("#p2#n #n I’m not used to this walk without my weapon. It makes me feel even more uneasy.").HideIfKey(GameKey::HasAmmo))
	.AddOptions(
		Option("I knock on the door to Anderssons office", "GetBadge4")
	),

	Entry("GetBadge4", "Commisioner Andersson sits behind her desk. She is almost as fat as the desk itself, and even though it’s freezing cold in here she seems to be sweating.#p3 She is grinning and licking her lips.#n #n Somewhere out in the corridor I hear someone crying. A weird sound.#p3 I shut the door behind me.#p2#n #n “You have the nerve to come back ? #s2After what you did?”#s1.#p3 Her eyes is bulging, almost as if they are to pop out of their sockets.")
	.AddOptions(
		Option("Beg to get the badge back (soul -1)", "GetBadgeBeg1"),
		Option("Be defiant (health -1)", "GetBadgeBegFight1")
	),

	Entry("GetBadgeBeg1", "“You always took credit for my results in the past” I tell her. “But as soon as the winds turn against me you leave me for the wolves?”#p3.#n #n It’s not a good way of begging for forgiveness, but I simply cannot stand her.#p2 She does not take it well!#p3#n #n “How dare you, you goddamn maniac!#p2 It is thanks to me that you are not rotting in prison right now!”#p3#n #n Then suddenly I see it!#p3 #cRMy badge!#cD#p3 It’s right there on the desk, under a stack of papers!")
	.AddOptions(
		Option("Grab it and run (soul -1)", "GetBadgeBeg2").TriggerKey(GameKey::HasBadge),
		Option("Be defiant (health -1)", "GetBadgeBegFight1")
	),

	Entry("GetBadgeBeg2", "#cRI grab the badge.#cD#p2 I am fast and she is slow.#p2 She screams as I run out through the door and into the ocean of desks. They stand up. They form a wall between me and the exit.#n #n “Get him” Andersson is shrieking from inside her office as she is struggling to get to her feet and come after me.")
	.AddText(
		OptionalText("#p2#n #n I feel very very naked without my gun right now").HideIfKey(GameKey::HasGun))
	.AddOptions(
		Option("Fire my gun to clear a path and escape (ammo -1 soul -1)", "GetBadgeBegShoot1").ShowIfKey(GameKey::HasAmmo),
		Option("Try to run past them", "GetBadgeBeg3")
	),

	Entry("GetBadgeBegShoot1", "I pull out my gun, and I see them all go stiff. Spineless maggots.#p2#n #n They do not open up for me though.")
	.AddOptions(
		Option("I have to show I mean business", "GetBadgeBegShoot2")
	),

	Entry("GetBadgeBegShoot2", "#e2#cR#s0BLAM#s1#cD#p3 the empty casing fall to the stone floor with a clatter.#p4 I told you I won’t let anything stand in my way!#p2 I have no problem reaching the exit. Everyone stands still like statues as I walk past them.")
		.TriggerKey(GameKey::CopKiller)
	.AddOptions(
		Option("I got my badge!", "Apartment2")
	),

	Entry("GetBadgeBeg3", "I try running past them, but hundreds of arms are ripping at me from all directions. I cannot move. Suddenly she stands in front of me. Andersson.")
	.AddOptions(
		Option("Continue", "GetBadgeCell1")
	),

	Entry("GetBadgeBegFight1", "#e4#p3She hits me right in the face. It hurts.")
	.AddOptions(
		Option("Hit her back", "GetBadgeBegFight2"),
		Option("Shoot her (ammo -1, soul -1)", "GetBadgeBegShoot2"),
		Option("Give up", "GetBadgeCell1")
	),

	Entry("GetBadgeBegFight2", "#e1#p3I kick her in the stomach. She grunts but she takes it.")
	.AddOptions(
		Option("Keep fighting (health -1)", "GetBadgeBegFight1"),
		Option("Shoot her (ammo -1, soul -1)", "GetBadgeBegShoot2"),
		Option("Give up", "GetBadgeCell1")
	),

	Entry("GetBadgeCell1", "I wake up in a dark cell.#p3 My head is hurting like hell.#p3 And someone in a cell close by is barking like a dog. Sickos all of them.#p3#n #n In the middle of the room stands #cRMartin#cD, my old friend. Rays of moonshine falls on him as he stands there with his broad smile.#p3 Somehow he ended up in the same cell as me. Weird.#n #n “You look like shit my old friend” he says, grinning.“Here, this will help!”.#n #n He offers me #cRa tiny blue pill#cD.")
	.TriggerKey(GameKey::HasFriend)
	.AddOptions(
		Option("Accept pill (soul -1 health +3)", "GetBadgeCell2A"),
		Option("Refuse pill", "GetBadgeCell2B")
	),

	Entry("GetBadgeCell2A", "I swallow the pill, and feel some strength returning to my limbs.#e8#p2 But also something else. Like part of my soul is falling off#e3.#p2 Martin is staring at me, still grinning.#p2#n #n “All right” he says, lets get out of here!")
	.AddOptions(
		Option("Continue", "GetBadgeCell3")
	),

	Entry("GetBadgeCells2B", "“Suit yourself” he says and puts the pill back into his pocket.#p2 Then he looks up.#p3 “All right, let’s get out of here!”")
	.AddOptions(
		Option("Continue", "GetBadgeCell3")
	),

	Entry("GetBadgeCell3", "The walls are cold but here and there roots and sticks stick out of the dirt. We climb out of the pit for what feels like hours, the faint light of the moon as the only source of light.#p3 As we finally gets to the top we are both soaked with sweat and we collapse onto the wet ground.#p3#n #n I feel my pockets. #cRThe badge is still in there!#cD#p3 I have it!")
		.TriggerKey(GameKey::HasBadge)
	.AddOptions(
		Option("Back to my apartment", "Apartment2")
	),

	Entry("GetDignity1", "Getting my dignity back is my ultimate goal!#p3 When I have my #cRvengeance#cD I shall have it back!#p3 I’ll show them all!")
	.AddOptions(
		Option("Lets get back home", "Apartment1").HideIfKey(GameKey::HasFriend),
		Option("Lets get back home", "Apartment2").ShowIfKey(GameKey::HasFriend)
	),

	Entry("GetDaughter1", "They dare take my daughter?#p2 My dear Sophia?#p3 This will not go unpunished!#n #n But I need to find her first!")
	.AddText(
		OptionalText("#p3#n #n And to proceed without my gun would not be wise, these people seems to be dangerous.").HideIfKey(GameKey::HasGun))
	.AddText(
		OptionalText("#p3#n #n If I had my badge back it would probably be much easier to gather information!").HideIfKey(GameKey::HasBadge))
	.AddOptions(
		Option("Martin has connections! Let him try and find out where she might be, and who it is that took her!", "GetDaughter2").ShowIfKey(GameKey::HasFriend),
		Option("I could let the technicians at work trace that weird phone call.", "GetDaughterWork1").ShowIfKey(GameKey::HasBadge),
		Option("Back to the apartment", "Apartment1").HideIfKey(GameKey::HasFriend),
		Option("Back to the apartment", "Apartment2").ShowIfKey(GameKey::HasFriend)
	),

	Entry("GetDaughter2", "Martin sneaks away. It takes several hours before he comes back.#p2 “I know where they have taken her”. He grins his broad grin again.#p3 “But, my friend, I’m afraid the information isn’t free.#p3 I need #cRa bit of your soul#cD in order to reveal the location!”")
	.AddOptions(
		Option("Force him at gunpoint (ammo -1)", "GetDaughter3").ShowIfKey(GameKey::HasAmmo),
		Option("Give him what he asks (soul -1)", "GetDaughter5"),
		Option("Sorry, I will have to find out some other way", "Apartment2")
	),

	Entry("GetDaughter3", "I immediately draw my gun and aim at his face. “You better tell me what I want, I am not messing around with this one!”. He still smiles. “Neither am I”.#e2#p3#n #n I fire my weapon right into his face")
	.AddOptions(
		Option("Continue", "GetDaughter4")
	),

	Entry("GetDaughter4", "He still stands there#p2, smiling. Did I miss?#p3 At gunpoint?#p3#n #n “You really think you can kill me that easy?#p3 Have you not started adding stuff together?” he asks.#p3 I have no clue what he’s talking about.")
	.AddOptions(
		Option("Give him what he wants (soul -1)", "GetDaughter5"),
		Option("Figure out another way", "Apartment2")
	),

	Entry("GetDaughter5", "My body shivers.#e3#p3#n #n “Fine” he says. I’ll show you!")
	.AddOptions(
		Option("Continue", "Showdown1")
	),

	Entry("GetDaughterWork1", "I stand in front of the police station. I take a deep breath and go in. I need to find the technicians that can trace the phone call that was made to my apartment.")
	.AddOptions(
		Option("Continue", "GetDaughterWorkGameOver").ShowIfKey(GameKey::CopKiller),
		Option("Continue", "GetDaughterWork2").HideIfKey(GameKey::CopKiller)
	),

	Entry("GetDaughterWorkGameOver", "I walk into the office, filled with desks. Filled with people. Spineless maggots that did not stand up for me when I needed their help. Last time I saw them they were standing still like statues. This time, to my surprise, they do not.#p3#n #n “Cop killer” they scream.#p3 “Cop killer”.#p3 They draw weapons.#p3 #s2They would never dare  #e4#cRBANG#cD#s1#p3#n #n I go down on one knee, blood pouring from my stomach. #p2What the fuc #e4#cRBANG#cD#p3#n The second bullet pierces my body.#p3 “Cop killer!”#p3#n #n The world goes dark around me. Vengeance! Dignity! Was it all just a dream?#p2 Was it in vain?#p2#n #n Why would they take my daughter away from me?#p2 I never meant to hurt anyone.#n #n#s2 I hear someone crying. It is Sophia. #s3And I hear a dog barking. #s4Then nothing."),
	
	Entry("GetDaughterWork2", "Getting the information I need is not easy. And it is not cheap. But I do get it.")
	.AddOptions(
		Option("It’s payback time", "Showdown1")
	),

	Entry("Showdown1", "I stand in front of this big square concrete building. Sophia is in there! My daughter. The building has no windows, but a huge guard dressed in black is posted outside.")
	.AddOptions(
		Option("I can easily take him down (ammo -1)", "Showdown3").ShowIfKey(GameKey::HasAmmo),
		Option("I can ask Martin to lure him away so I can sneak in (soul -1)", "Showdown2")
	),

	Entry("Showdown2", "Martin smile his broad smile. “No problems buddy, but you know what I want! #cRA piece of your soul#cD”. I give it to him. It hurts!#e3 And he disappears in the night. The guard is gone.")
	.AddOptions(
		Option("Let’s go in", "ShowdownInside")
	),

	Entry("Showdown3", "I aim at the guard. #e1#cRBANG#cD#p3. The sound of the gunshot echoes between the buildings as he falls over. I run past his lifeless body and into the building.")
	.AddOptions(
		Option("#I’m coming Sophia", "ShowdownInside")
	),

	Entry("ShowdownInside", "I find her inside! But she looks afraid. Terrified! “Dad? No! What are you doing here? Go away!”#n #n I try to calm her, but she screams and screams! In the streets there’s the sound of sirens.#n #n It feels like my soul is shattering.#p3 I can’t take it all in.#p3 She is crying now. I hear the barking of dogs coming up the staircase.#p3 I step out of her room and shut the door.#p3#n #n Someone is screaming outside with a megaphone that I should release the hostage.#n #n")
	.AddText(
		OptionalText("#s2I look down at the gun still in my hand. Still a chance to end it all #cRwith dignity#cD!#p3 I put the gun to my head and pull the trigger.").ShowIfKey(GameKey::HasAmmo))
	.AddText(
		OptionalText("#s2As the door break down I hear them scream that I should lie down.#p3 No.#p3 There is one more thing I’m missing. #cRDignity#cD. I walk towards them. The sound from their rifles echoes through the corridor.").HideIfKey(GameKey::HasAmmo)),

	Entry("GameOverSouls", "It feels like something in my body shatters. I fall down on my knees and stare into my palms. In the distant I hear a dog howling.#n #n As my soul breaks I hear someone laughing..."),

	Entry("GameOverHealth", "Blood is bubbling out of my body and I fall over, unable to move. Is this it? This cannot be it! I still have work to do.#n #n But it’s getting hard to breathe, and my vision blurs.As the world fades I hear Sophia crying.But she isn’t crying because of her daddy is dying.She is crying over what her daddy did..."),
};




Entry* GetEntry(string ID) {
	int len = (sizeof(entries) / sizeof(*entries));
	for (int i = 0; i < len; i++) {
		if (entries[i].ID == ID) {
			return &entries[i];
		}
	}
	return NULL;
}
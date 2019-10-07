#include <string>
#include <vector>
#include "Data.h"

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

	Entry("Apartment1", "My apartment looks like a crime scene.")
	.AddText(
		OptionalText("#n #n I don’t want to call it in, I don’t trust the spineless maggots down at the station.#p1 Maybe #cBMartin#cD could help though. He’s a tough motherfucker.").HideIfKey(GameKey::CalledMartin))
	.AddOptions(
		Option("Call #cBMartin#cW", "CallMartin").HideIfKey(GameKey::CalledMartin).TriggerKey(GameKey::CalledMartin),
		Option("I need to get my gun back", "GetGun1"),
		Option("I need to get my badge back", "GetBadge1"),
		Option("I need to get my dignity back", "GetDignity1"),
		Option("I need to get my daughter back", "GetDaughter1")
	),

	Entry("CallMartin", "It takes me several phone calls before I get the answers I need.#n #n #cBMartin#cD is away on a #cWblack ops mission again#cD. Probably #cWIraq or Syria#cD. #cR#s2He won’t be back for at least 6 months.#cD#s1 It means I have to take care of this on my own.")
	.AddOptions(
		Option("Continue", "Apartment1")
	),

	Entry("Apartment2", "").TriggerKey(GameKey::HasFriend)
	.AddText(
		OptionalText("Back in the apartment again.#n #n In the middle of the chaos stands #cBMartin#cD. He must have come home earlier from his mission.#n #n Anyone who has met Martin knows that he is #cRnothing short of a demon!#cD #p2With his broad smile that never reaches his eyes. And with killing efficiency whatever he puts his mind to!#n #n #cG“I heard you were in trouble”#cD he says, still with that smile. #cG“I thought you needed some help!”#cD#n #n Outside the sun is setting.")
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
	

	Entry("GetGun1", "I’ve been on the force for ten years. I feel naked without a gun. Luckily I have a spare one.#n #n It’s just that #cBSofia#cD made me promise never to use it, so I dug it down in the garden.#n #n Also there’s #cBLazlo#cD. That shithead, petty crime lord, who somehow seems to be untouchable by the law. I’ve crossed him a couple of times, and he can be intimidated into giving me a weapon.")
	.AddOptions(
		Option("Dig up the gun in the garden (soul -1, ammo +1)", "Garden").TriggerKey(GameKey::HasGun),
		Option("Visit Lazlo", "Lazlo"),
		Option("Nevermind, I’ll get by without a gun", "Apartment1").HideIfKey(GameKey::HasFriend),
		Option("Nevermind, I’ll get by without a gun", "Apartment2").ShowIfKey(GameKey::HasFriend)
	),

	Entry("Garden", "The mist is thick outside,#p1 making it hard to see more than a few meters.#p1 The vague shapes of the trees around me look like deformed bodies watching me.#p2 In the distance I hear someone crying.#p1 The sound is driving me nuts.#p2#n #n I dig up the wooden box and open it. #cRThe revolver#cD is in it. And #cRa single bullet#cD#e5.#p1 I feel ashamed as I take them,#p2 I promised #cBSofia#cD!#e3#p3 But now she’s gone,#p1 and she needs me.#p2#n #n I might need more than a single bullet though...")
	.AddOptions(
		Option("Investigate the crying sound (soul -1)", "Neighbour"),
		Option("Maybe I should visit #cBLazlo#cW anyway", "Lazlo"),
		Option("One bullet will be enough", "Apartment2")
	),

	Entry("Neighbour", "The crying sound seems to come from #cBmy neighbour#cD. She is standing in the lawn, hunched over something. Another hysterical woman, just what I need... The wet, thick mist makes it hard to see. I move closer. She looks smaller...#n #n She looks up. #cG“You took the gun! You promised you would never take the gun!”#cD#e3.#p3 #cRThe dog in her lap is growling at me.#cD")
	.AddOptions(
		Option("Shoot the dog (ammo -1)", "Neighbour2").ShowIfKey(GameKey::HasAmmo),
		Option("Run away", "Apartment2")
	),

	Entry("Neighbour2", "#s0#cRBang!#cD#e2#n #n That dog was going to attack!#p1 I had no choice!#p1 She keeps on crying.#n #n But I’m out of bullets.#p2 I should either pay #cBLazlo#cD a visit, or just keep going without a weapon.")
	.AddOptions(
		Option("Visit #cBLazlo#cW", "Lazlo"),
		Option("Go back inside", "Apartment2")
	),


	Entry("Lazlo", "I manage to arrange a meeting with #cBLazlo#cD.#p3 We’ve met a couple of times and scratched each others backs. But he is a slippery bastard!#p2 His #cRhuge dog#cD lying by his feet, black eyes watching me.#p3 His raspy voice tears through the fog.#n #n #cG“So now it suits you to beg for favours#p2, you piece of shit!#p3 I heard you were kicked out of the force!#p2 Actually... I hear all kind of things about you lately!”#cD#p3#n #n That son of a bitch. I’ve had his back more times than I can count, but he thinks he can treat me like this?#p2 I would kick his ass if it wasn’t for that huge-ass dog of his.#p2#n #n #cG“Tell me what, I’ll help you out if you do me a small favour!”#cD#p2#n #n (If I could flash my badge it would shut his smirky face)")
	.AddOptions(
		Option("What favour?", "LazloSoul1"),
		Option("Attack him and take what I need (ammo -1 and health -1)", "LazloShoot1").ShowIfKey(GameKey::HasAmmo),
		Option("Attack him and take what I need (health -3)", "LazloAtkUnarmed1").HideIfKey(GameKey::HasAmmo),
		Option("Show him the badge", "LazloBadge1").ShowIfKey(GameKey::HasBadge)
	),

	Entry("LazloSoul1", "He smirks at me#p2, showing a fine line of white teeth.#p3#n #n #cG“Just give me #cRa piece of your soul!#cG”#cD he says...")
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

	Entry("LazloShootDog1", "#e2#s0#cRBANG#cD#s1#p3 The dog is out! Just #cBLazlo#cD to deal with!#p3 He screams and takes a swing at me.")
	.AddOptions(
		Option("Continue", "LazloShootDog2")
	),

	Entry("LazloShootDog2", "His fist hits my face!#e4#p3 ")
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

	Entry("LazloBadge1", "I show him the badge and his smile goes away.#p1 He looks suspiciously at me.#n #n #cG“All right! Fine!”#cD#p1 he says and tosses me a handgun. #p2Loaded with 6 bullets.#p2 #cG“Get out of here you piece of shit”#cD.")
	.AddOptions(
		Option("Lets get back home", "Apartment2")
	),

	Entry("GetBadge1", "I have no choice, I need my badge back. I need to go back to my #cBold boss#cD and tell her how incredibly sorry I am, and beg her to take me back.#n #n It’s crazy. #s2It is THEY who should beg ME to come back.#s1 I always did what was needed. I never complained.")
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
		Option("I knock on the door to #cBAnderssons#cD office", "GetBadge4")
	),

	Entry("GetBadge4", "#cBCommisioner Andersson#cD sits behind her desk. She is almost as fat as the desk itself, and even though it’s freezing cold in here she seems to be sweating.#p3 She is grinning and licking her lips.#n #n Somewhere out in the corridor I hear someone crying. A weird sound.#p3 I shut the door behind me.#p2#n #n #cG“You have the nerve to come back ? #s2After what you did?”#cD#s1.#p3 Her eyes is bulging, almost as if they are to pop out of their sockets.")
	.AddOptions(
		Option("Beg to get the badge back (soul -1)", "GetBadgeBeg1"),
		Option("Be defiant (health -1)", "GetBadgeBegFight1")
	),

	Entry("GetBadgeBeg1", "#cG“You always took credit for my results in the past”#cD I tell her. #cG“But as soon as the winds turn against me you leave me for the wolves?”#cD#p3.#n #n It’s not a good way of begging for forgiveness, but I simply cannot stand her.#p2 She does not take it well!#p3#n #n #cG“How dare you, you goddamn maniac!#p2 It is thanks to me that you are not rotting in prison right now!”#cD#p3#n #n Then suddenly I see it!#p3 #cRMy badge!#cD#p3 It’s right there on the desk, under a stack of papers!")
	.AddOptions(
		Option("Grab it and run (soul -1)", "GetBadgeBeg2").TriggerKey(GameKey::HasBadge),
		Option("Be defiant (health -1)", "GetBadgeBegFight1")
	),

	Entry("GetBadgeBeg2", "#cRI grab the badge.#cD#p2 I am fast and she is slow.#p2 She screams as I run out through the door and into the ocean of desks. They stand up. They form a wall between me and the exit.#n #n #cG“Get him”#cD Andersson is shrieking from inside her office as she is struggling to get to her feet and come after me.")
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

	Entry("GetBadgeBegShoot2", "#e2#cR#s0BLAM#s1#cD#p3 the empty casing fall to the stone floor with a clatter.#p4 I told you I won’t let anything stand in my way!#p2 I have no problem reaching the exit. #cREveryone stands still like statues as I walk past them.#cD")
		.TriggerKey(GameKey::CopKiller)
	.AddOptions(
		Option("I got my badge!", "Apartment2")
	),

	Entry("GetBadgeBeg3", "I try running past them, but hundreds of arms are ripping at me from all directions. I cannot move. Suddenly she stands in front of me. #cBAndersson#cD.")
	.AddOptions(
		Option("Continue", "GetBadgeCell1")
	),

	Entry("GetBadgeBegFight1", "She hits me right in the face#e4.#p3 It hurts.")
	.AddOptions(
		Option("Hit her back", "GetBadgeBegFight2"),
		Option("Shoot her (ammo -1, soul -1)", "GetBadgeBegShoot2").ShowIfKey(GameKey::HasAmmo),
		Option("Give up", "GetBadgeCell1")
	),

	Entry("GetBadgeBegFight2", "I kick her in the stomach#e1.#p3 She grunts but she takes it.")
	.AddOptions(
		Option("Keep fighting (health -1)", "GetBadgeBegFight1"),
		Option("Shoot her (ammo -1, soul -1)", "GetBadgeBegShoot2").ShowIfKey(GameKey::HasAmmo),
		Option("Give up", "GetBadgeCell1")
	),

	Entry("GetBadgeCell1", "I wake up in a dark cell.#p3 My head is hurting like hell.#p3 And someone in a cell close by is barking like a dog.#n #n In the middle of the room stands #cBMartin#cD, my old friend. Rays of moonshine falls on him as he stands there with his broad smile.#p3 Somehow he ended up in the same cell as me. Weird.#n #n #cG“You look like shit my old friend”#cD he says, grinning.#cG“Here, this will help!”#cD.#n #n He offers me #cRa tiny blue pill#cD.")
	.TriggerKey(GameKey::HasFriend)
	.AddOptions(
		Option("Accept pill (soul -1 health +3)", "GetBadgeCell2A"),
		Option("Refuse pill", "GetBadgeCell2B")
	),

	Entry("GetBadgeCell2A", "I swallow the pill, and feel some strength returning to my limbs.#e8#p2 But also something else. Like part of my soul is falling off#e3.#p2 #cBMartin#cD is staring at me, still grinning.#p2#n #n #cG“All right”#cD he says, #cG“lets get out of here!”#cD")
	.AddOptions(
		Option("Continue", "GetBadgeCell3")
	),

	Entry("GetBadgeCell2B", "#cG“Suit yourself”#cD he says and puts the pill back into his pocket.#p2 Then he looks up.#p3 #cG“All right, let’s get out of here!”#cD")
	.AddOptions(
		Option("Continue", "GetBadgeCell3")
	),

	Entry("GetBadgeCell3", "The walls are cold but here and there roots and sticks stick out of the dirt. We climb out of the pit for what feels like hours, the faint light of the moon as the only source of light.#p3 As we finally gets to the top we are both soaked with sweat and we collapse onto the wet ground.#p3#n #n I feel my pockets. #cRThe badge is still in there!#cD#p3 I have it!")
		.TriggerKey(GameKey::HasBadge)
	.AddOptions(
		Option("Back to my apartment", "Apartment2")
	),

	Entry("GetDignity1", "Getting my dignity back is my ultimate goal!#p3 When I have my #cRvengeance#cD I shall have it back!")
	.AddOptions(
		Option("Lets get back home", "Apartment1").HideIfKey(GameKey::HasFriend),
		Option("Lets get back home", "Apartment2").ShowIfKey(GameKey::HasFriend)
	),

	Entry("GetDaughter1", "They dare take my daughter?#p2 My dear ”#cDSophia?#cD#p3 This will not go unpunished!#n #n But I need to find her first!")
	.AddText(
		OptionalText("#p3#n #n And to proceed without my gun would not be wise, these people seems to be dangerous.").HideIfKey(GameKey::HasGun))
	.AddText(
		OptionalText("#p3#n #n If I had my badge back it would probably be much easier to gather information!").HideIfKey(GameKey::HasBadge))
	.AddOptions(
		Option("”#cDMartin#cW has connections! Let him try and find out where she might be, and who it is that took her!", "GetDaughter2").ShowIfKey(GameKey::HasFriend),
		Option("I could let #cBthe technicians#cW at work trace that weird phone call.", "GetDaughterWork1").ShowIfKey(GameKey::HasBadge),
		Option("Back to the apartment", "Apartment1").HideIfKey(GameKey::HasFriend),
		Option("Back to the apartment", "Apartment2").ShowIfKey(GameKey::HasFriend)
	),

	Entry("GetDaughter2", "#cBMartin#cD sneaks away. It takes several hours before he comes back.#p2 #cG“I know where they have taken her”#cD. He grins his broad grin again.#p3 #cG“But, my friend, I’m afraid the information isn’t free.#p3 I need #cRa bit of your soul#cG in order to reveal the location!”#cD")
	.AddOptions(
		Option("Force him at gunpoint (ammo -1)", "GetDaughter3").ShowIfKey(GameKey::HasAmmo),
		Option("Give him what he asks (soul -1)", "GetDaughter5"),
		Option("Sorry, I will have to find out some other way", "Apartment2")
	),

	Entry("GetDaughter3", "I immediately draw my gun and aim at his face. #cG“You better tell me what I want, I am not messing around with this one!”#cD. He still smiles. #cG“Neither am I”#cD.#e2#p3#n #n I fire my weapon right into his face")
	.AddOptions(
		Option("Continue", "GetDaughter4")
	),

	Entry("GetDaughter4", "He still stands there#p2, smiling. Did I miss?#p3 At gunpoint?#p3#n #n #cG“You really think you can kill me that easy?#p3 Have you not started adding stuff together?”#cD he asks.#p3 I have no clue what he’s talking about.")
	.AddOptions(
		Option("Give him what he wants (soul -1)", "GetDaughter5"),
		Option("Figure out another way", "Apartment2")
	),

	Entry("GetDaughter5", "My body shivers.#e3#p3#n #n #cG“Fine”#cD he says. I’ll show you!")
	.AddOptions(
		Option("Continue", "Showdown1")
	),

	Entry("GetDaughterWork1", "I stand in front of the police station. I take a deep breath and go in. I need to find #cBthe technicians#cD that can trace the phone call that was made to my apartment.")
	.AddOptions(
		Option("Continue", "GetDaughterWorkGameOver").ShowIfKey(GameKey::CopKiller),
		Option("Continue", "GetDaughterWork2").HideIfKey(GameKey::CopKiller)
	),

	Entry("GetDaughterWorkGameOver", "I walk into the office, filled with desks. Filled with people. Spineless maggots that did not stand up for me when I needed their help. Last time I saw them they were standing still like statues. This time, to my surprise, they do not.#p3#n #n #cG“Cop killer”#cD they chant.#p1 #cG“Cop killer”#cD.#p3 They draw weapons.#p3 #s2They would ne#s9#e4#cRBANG#cD#s1#p3#n #n I go down on one knee, blood pouring from my stomach. #p2What the fuc#e4#cR#s9BANG#s1#cD#p3#n The second bullet pierces my body.#p3 #cG“Cop killer!”#cD.#p3#n #n The world goes dark around me. #s2I hear someone crying. It is #cBSophia#cD. #s3And I hear a dog barking. #s4Then nothing.")
	.AddText(
		OptionalText("#p4#n #n #n #cR#s3 Game Over!#n Thanks for playing!")),

	Entry("GetDaughterWork2", "Getting the information I need is not easy. And it is not cheap. But I do get it.")
	.AddOptions(
		Option("It’s payback time", "Showdown1")
	),

	Entry("Showdown1", "I stand in front of this big square concrete building.#p2 #cBSophia#cD is in there!#p3 My daughter.#p2 The building has no windows, but a #cBhuge guard#cD dressed in black is posted outside.")
	.AddOptions(
		Option("I can easily take him down (ammo -1)", "Showdown3").ShowIfKey(GameKey::HasAmmo),
		Option("I can ask #cBMartin#cW to lure him away so I can sneak in (soul -1)", "Showdown2")
	),

	Entry("Showdown2", "#cBMartin#cD smile his broad smile. #cG“No problems buddy, but you know what I want!#p3 #cRA piece of your soul#cG”#cD.#p2 I give it to him. It hurts!#e3#p3 And he disappears in the night.#p2 #cBThe guard#cD is gone.")
	.AddOptions(
		Option("Let’s go in", "ShowdownInside")
	),

	Entry("Showdown3", "I aim at #cBthe guard#cD. #e2#cRBANG#cD#p3. The sound of the gunshot echoes between the buildings as he falls over. I run past his lifeless body and into the building.")
	.AddOptions(
		Option("I’m coming #cBSophia#cD", "ShowdownInside")
	),

	Entry("ShowdownInside", "I find her inside! But she looks afraid.#p2 Terrified!#p2 #cG“Dad?#p2 No!#p2 What are you doing here?#p1 Go away!”#p2#cD#n #n I try to calm her,#p1 but she screams and screams!#p3 In the streets there’s the sound of sirens.#p3#n #n It feels like my soul is shattering.#p3 I can’t take it all in.#p3 She is crying now.#p1 I hear the barking of dogs coming up the staircase.#p3 I step out of her room and shut the door.#p3#n #n Someone is screaming outside with a megaphone #s3that I should release the hostage.#p2#s1#n #n ")
	.AddText(
		OptionalText("I look down at the gun still in my hand.#p1#s2 Still a chance to end it all #cRwith dignity#cD!#p3 I put the gun to my head and pull the trigger.").ShowIfKey(GameKey::HasAmmo))
	.AddText(
		OptionalText("As the door break down I hear them scream that I should lie down.#p3#s2 No.#p3 There is one more thing I’m missing. #s1#cRDignity#cD.#s2 I walk towards them.#p1 The sound from their rifles echoes through the corridor.").HideIfKey(GameKey::HasAmmo))
	.AddText(
		OptionalText("#p4#n #n #n #cR#s3 Game Over!#n Thanks for playing!")),

	Entry("GameOverSouls", "It feels like something in my body shatters. I fall down on my knees and stare into my palms. In the distant I hear a dog howling.#n #n As my soul breaks I hear someone laughing...")
	.AddText(
		OptionalText("#p4#n #n #n #cR#s3 Game Over!#n Thanks for playing!")),

	Entry("GameOverHealth", "Blood is bubbling out of my body and I fall over, unable to move. Is this it? This cannot be it! I still have work to do.#n #n But it’s getting hard to breathe, and my vision blurs. As the world fades I hear #cBSophia#cD crying. But she’s not crying because of my death... I think she is cries over what I did...")
	.AddText(
		OptionalText("#p4#n #n #n #cR#s3 Game Over!#n Thanks for playing!")),
};


string ValidateEntryLinks() {
	string s = "";
	int len = (sizeof(entries) / sizeof(*entries));
	for (int i = 0; i < len; i++) {
		Entry &e = entries[i];
		int numOpts = e.options.size();
		for (int ii = 0; ii < numOpts; ii++) {
			Entry *check = GetEntry(e.options[ii].link);
			if (check == NULL) {
				s += "Entry: " + e.ID + " invalid link: " + e.options[ii].link + "\n";
			}
		}
	}
	return s;
}



Entry* GetEntry(string ID) {
	int len = (sizeof(entries) / sizeof(*entries));
	for (int i = 0; i < len; i++) {
		if (entries[i].ID == ID) {
			return &entries[i];
		}
	}
	return NULL;
}
# Hack no 1 - Turning on godmode

The following text will reveal you how to become a god in almost any game easily. We will choose
Mafia as it is my favourite game.

At first, start the game and start playing. When your game is ready and you are free to move with
your character, then start up your favourite memory searching program. We will use `Cheat Engine`
for this purposes.

Now here is the plan. Your character is most likely just a object inside the game's engine, which
handles its attributes. To become a god, we will need to `prevent game rewriting object's attribute`, 
which stands for player's health. But we need to find the address of heath at first !

##A trivial algorithm how to find that address using memory searching program:

1. Find out what's the value of your current health. Usually, this is displayed somewhere in HUD.
2. Search for all addresses in game which has the exactly same value as your health is.
3. Decrease your healt ! Bump into objects using a car, get yourself shot by a mobster or fall down
   from the hill !
4. Now use Cheat Engine to remain only those addresses which has the same value as your current
   health.
5. Repeat from step 3 until the set of addresses is small-enough and can be examined manually.

After a few iterations of the algorithm, two scenarious can occur:
1. You have found right address which when written to handles the value you
put inside and actually controls the behaviour of the game.
2. Your set has become empty - in this case, either you spoiled something
while looking for changed addresses, or the game doesn't keep the health value the way 
you thought so. In that case, you can use an alterned algorithm - instead of looking for 
an exact value, you can actually search for addresses, whose value has decreased / increased.

## Success
Hurray ! You have just found an address which allows you to change your health. To become a god,
       you can use Cheat Engine's feature which freezes the address.

## What can I use this hack for

What we've just learnt is how simple attributes can be revelead using memory comparison methods.
This algorithm can in general be used for:
* finding addresses for different objects and their attributes (health, armor, ammunition)

# 🧠 Memory Card Game

This morning I built my first memory game and it's actually a lot of fun to play! Plus each matched pair lights up with its own rainbow gradient, the final board looks like a color explosion! (note to self, maybe make it actually explode in the future!?!)

## What you'll see
A 4x4 grid of mystery cards that do this sick 3D flip animation when you click them. Each card has an emoji buddy hiding somewhere in the grid, and when you find a match, they light up with their own unique gradient color! The game tracks your moves and time, and when you finish, a dramatic black overlay slides over everything to show your stats. The coolest part? The completed board looks like a rainbow checkerboard through the victory screen!

## How to run this
1. Save the `memory_game.html` file
2. Double-click to open in your browser
3. Start clicking cards to find the matching pairs!

## How it works
This game is pure CSS and JavaScript magic! Here's what's happening behind the scenes:

1. **The Setup**: I create 8 emoji pairs (that's 16 cards total) and shuffle them using the Fisher-Yates algorithm (fancy name for "really good randomizing")

2. **The 3D Flip**: Each card is actually TWO divs stacked on top of each other! The magic CSS:
   ```css
   transform-style: preserve-3d;
   transform: rotateY(180deg);
   ```
   This literally rotates the card in 3D space - like spinning a real card!

3. **The Matching Logic**: When you click two cards, I check if their `data-card-value` attributes match. If yes, they get the `matched` class and stay flipped forever. If no, they flip back after 1 second (just enough time to memorize them!)

4. **The Rainbow Effect**: Each emoji has its own gradient color that only shows when matched:
   ```css
   .card.matched[data-card-value="🎮"] .card-back {
       background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
   }
   ```

5. **The Timer**: Starts counting the moment you flip your first card - no cheating by studying the board first!

## Try changing this
- **Line 218**: Change the `cardEmojis` array to use your own emoji theme (try making it all food emojis! 🍕🍔🌮)
- **Line 49**: Make it a 6x6 grid by changing `grid-template-columns: repeat(6, 1fr)` (you'll need 18 emoji pairs though!)
- **Line 306**: Speed up the flip-back time from `1000` to `500` milliseconds for EXTREME difficulty
- **Lines 73-103**: Remix the gradient colors for each matched pair - try making them all shades of blue or go full neon!
- **Line 107**: Adjust the match animation - make cards grow bigger with `scale(1.3)` for more drama

## What I learned
Okay, so CSS 3D transforms completely blew my mind! I had no idea you could make elements actually flip in 3D just with CSS. The breakthrough moment was discovering `backface-visibility: hidden` - without this, you'd see the back of the card showing through backwards (super weird). 

The trickiest part was the game state management. I kept running into this bug where if you clicked too fast, you could flip three cards at once and break everything! Fixed it by checking if two cards are already flipped before allowing another click. Also learned that `data-` attributes are perfect for storing game values right on the HTML elements.

Best discovery: Using CSS attribute selectors to give each emoji pair its own color. I wasn't even sure you could target elements based on their data attributes like that! Now I want to add this rainbow effect to everything!
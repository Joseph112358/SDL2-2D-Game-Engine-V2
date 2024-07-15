TODO list
* Create an "NPC" entity, write a script for path finding
* Fix diagonal behaviour so distance travelled is constant.
* Interactable map. E.g. sow plants, open chest, use terminal

* Decide on how to do rendering, either:
  * Player class have a renderPlayer(Renderer * renderer); function
  * Game class has a renderPlayer(Player * player) function.
  * Create a renderer class?


* June 15th TODO
  * Hit box: the whole entity, if a bullet or something collides with it, damage is done
  * Collision box? At the players feet, dictates where entity can walk
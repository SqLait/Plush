# Pleasant Lua User Shell

Plush is project that aims to make powerfull shell with the looks, that does not compromise on performance.
Scripting can be achieved in both C and Lua.

# Why Plush, Don't we already have shells that do a lot of things?

Yes, this shell brings nothing major to the table. However this shell does try to fix a lot of the issues that plague modern shells.
Lets take some shells and list their pros and cons:

## zsh:
* Pros:
    - Great community support
    - A lot of plugins
* Cons:
    - zsh is very slow compared to standard bash
    - Uses sh for scripting, which is objectively one of the worst scripting languages
    - Is pretty old so can lack default features of mordern shells

## fish:
* Pros:
    - Features built into the shell itself
    - Lightweight
* Cons:
    - In order to script you have to learn fish, which is not as popular as sh
    - Theme, prompt and other configuration needs to be done through a web server

# How does Plush fix these issues?

One of the key philosophy's that the Plush shell follows is "Keep it simple! stupid...", "If it ain't broke, don't fix it." and "Don't re-invent the wheel."
Because of this plush uses C for its backbone, The core utils for navigation, and most importantly: Lua as its scripting language.

Why lua? Lua is a very proven language that is used as a embedded language in game engine's, text editors. But not really in shells. And since lua is very
fast and powerfull it seems like a no brainer to use it in a shell that does not want to sacrifice on performance.

# How to customize?

All customization can be done in the init.lua file.

# > IMPORTANT
Because of the sheer determination of this project things will take longer. For example getting lua extendability with the core utils to work. Or writing your own shell
libs can be a lot of work. Therefore this project will not be finished for a long time.

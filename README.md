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

# IMPORTANT

The shell will be in development for a long time. Contributions are welcome but don't expect a well working product in the near future.

# How to customize?

When first starting the shell you get prompted to create a config. Hit Y so you can start using lua to customize the behaviour of your shell.
But that is not all. if you create a prompt.lua file you can create your own prompt!

NOTE: In the future this behaviour will change. I am currently working on implementing a init.lua file that will run all your configs in the shell.
This will also creatly improve the performance of the shell instead of having one lua runtime per script, since now it will use one per shell.
You will probably have to use special variables in order to change things like the prompt.

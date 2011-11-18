Views Fast Search Node Type Ranking
-----------------------------------
Author: JacobSingh <jacobsingh@gmail.com>

Provides node type ranking to vfs.

It's in a beta phase, but works, so please give feedback on what is needed.

To install:

Enable the module.

This will create the table vfs_ranking_nodetype which has two columns, type and
search_weight.

Go to admin/settings/vfs_ranking_nodetype

Here you can set a weighting from 0-10 for each type. Currently, the vfs search
results score is simply multiplied by this number. So if you set the weight of
stories to 5 and the weight of pages to 2, a story which previously had a score
of 5, will now be 25, and a page which previously had a score of 10 will be 20,
so now the story will come first.

Enjoy!

Note: This is a good example on how to extend search ranks - Doug Green.


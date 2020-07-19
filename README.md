# Native Balanced binary tree for Ruby

Ruby bindings to [GTree - balanced binary tree from GLib library](https://developer.gnome.org/glib/stable/glib-Balanced-Binary-Trees.html) .

In most cases it is behave same as Hash, but keys will be ordered by passed comparator.

Basic usage:

```ruby
require 'native_btree'

# Pass comparator for keys as block
tree = NativeBTree::BTree.new { |a, b|  a <=> b }

tree[:a1] = '111'
tree[:c3] = '333'
tree[:b2] = '222'

tree.each { |k, v| puts "#{k} => #{v}" }

# a1 => 111
# b2 => 222
# c3 => 333
# nil

tree.size
# 3

tree.height
# 2
```

Trees is may comparable by `==` or `.eql?` operator.
Trees will be equal if all keys and all value is equal in both.

# GLib Balanced binary tree (GTree) bindings for Ruby

[![Ruby](https://github.com/unixs/ruby-native-btree/actions/workflows/main.yml/badge.svg)](https://github.com/unixs/ruby-native-btree/actions/workflows/main.yml)
[![Gem Version](https://badge.fury.io/rb/native_btree.svg)](https://badge.fury.io/rb/native_btree)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)


[GTree - balanced binary tree from GLib library](https://docs.gtk.org/glib/struct.Tree.html)

In most cases it will behave same as Hash, but keys will be ordered by passed comparator.

## Requirements

* **CMake** build tool version **>= 3.5.0**, >= 3.14.0 will be cool.
* `pkg-config` tool
* **GLib** library
  * On Ubuntu run:
  ```bash
  sudo apt-get install pkg-config cmake libglib2.0-dev
  ```
  * On MacOS run:
  ```
  brew install pkg-config cmake glib
  ```
  * On FreeBSD use pkg or ports.
  * On windows use Google. I don't really know how it can work at this moment... But i think it's possible

**Check CMake tool version!**

## Basic usage

### Example
```ruby
require 'native_btree'

# Pass comparator for keys as block
tree = NativeBtree::Btree.new { |a, b|  a - b }

tree[1] = '111'
tree[3] = '333'
tree[2] = '222'

tree.each { |k, v| puts "#{k} => #{v}" }

# 1 => 111
# 2 => 222
# 3 => 333
# nil

tree.size
# 3

tree.height
# 2
```

### Native int comparator
Will behave like an array with negative indexes)
```ruby
# Pass comparator for keys as block
tree = NativeBtree::Btree.new(NativeBtree::Btree::INT_COMPARATOR)

tree[-2] = 22
tree[-1] = 1
tree[0] = 100
tree[5] = 55

tree.to_a

#[
#    [0] [
#        [0] -2,
#        [1] 22
#    ],
#    [1] [
#        [0] -1,
#        [1] 1
#    ],
#    [2] [
#        [0] 0,
#        [1] 100
#    ],
#    [3] [
#        [0] 5,
#        [1] 55
#    ]
#]
```

## API ref

You must provide your own comparator for keys in `new` class method block.

### API methods

In general this class behave same as Hash

Implemented methods:

* `[]= (alias: set)`
* `[] (alias: get)`
* `==`
* `delete`
* `size`
* `height`
* `each` (NB! block is required) (NB! block is required)
* `include?`
* `clear`
* `to_h`
* `to_a`
* `to_proc`
* `filter` (alias: select)
* `filter!` (alias: select!)
* `each_value`
* `each_key`
* `search_before` (GLib version >= 2.68) - Select keys <= first arg, ret new Btree
* `search_after` (GLib version >= 2.68) - Select keys >= first arg, ret new Btree
* `empty?`
* `reverse_each`

You can mix in the `Enumerable` module if additional methods are needed.

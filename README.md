# GLib Balanced binary tree (GTree) bindings for Ruby

[![Ruby](https://github.com/unixs/ruby-native-btree/actions/workflows/main.yml/badge.svg)](https://github.com/unixs/ruby-native-btree/actions/workflows/main.yml)
[![Gem Version](https://badge.fury.io/rb/native_btree.svg)](https://badge.fury.io/rb/native_btree)

[GTree - balanced binary tree from GLib library](https://docs.gtk.org/glib/struct.Tree.html)

In most cases it will behave same as Hash, but keys will be ordered by passed comparator.

## Requirements

* **CMake** build tool version **>= 3.14.0**
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

## API ref

You must provide your own comparator for keys in `new` class method block.

### Methods

* `[]= (alias: set)`
* `[] (alias: get)`
* `delete`
* `size`
* `height`
* `each`

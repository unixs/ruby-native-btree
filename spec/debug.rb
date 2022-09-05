# rubocop:disable all

require_relative "../lib/native_btree/native_btree"

tree = NativeBtree::Btree.new

GC.start

tree[3] = {a: 'value 3'}
tree[1] = {a: 'value 1'}
tree[2] = {a: 'value 2'}
tree[16] = {a: 'value 16'}
tree[0] = {a: 'value 0'}

GC.start

block = ->(key) { "#{key} is not found" }
puts tree.delete(77, &block)

tree = null

GC.start

puts "exit 0"
# rubocop:disable all

require_relative "../lib/native_btree/native_btree"

NativeBtree::Btree.include(Enumerable)

tree = NativeBtree::Btree.new() {|a, b| a - b }
tree2 = NativeBtree::Btree.new() {|a, b| a - b }

GC.start

tree[3] = {a: 'value 3'}
tree[1] = {a: 'value 1'}
tree[2] = {a: 'value 2'}
tree[16] = {a: 'value 16'}
tree[0] = {a: 'value 0'}

GC.start

block = ->(key) { "#{key} is not found" }
puts tree.delete(77, &block)

puts tree.to_h

pr = tree.to_proc

puts pr


tree.clear
(1..1000000).each do |i|
  tree[i] = i+2
  tree2[i] = i+2
end

puts tree == tree2

GC.start

puts "exit 0"

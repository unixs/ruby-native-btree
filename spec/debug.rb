# rubocop:disable all

require_relative "../lib/native_btree/native_btree"

NativeBtree::Btree.include(Enumerable)

tree = NativeBtree::Btree.new() {|a, b| a - b }

GC.start

tree[3] = {a: 'value 3'}
tree[1] = {a: 'value 1'}
tree[2] = {a: 'value 2'}
tree[16] = {a: 'value 16'}
tree[0] = {a: 'value 0'}

GC.start

block = ->(key) { "#{key} is not found" }
puts tree.delete(77, &block)

tree2 = tree.filter!() { true }

puts tree.to_h

pr = tree.to_proc

puts pr


tree.clear
tree[1] = 15
tree[2] = 22
tree[3] = 33
tree[4] = 44
tree[5] = 55
tree[6] = 66
tree[7] = 77

puts tree.select_before(4).to_h

puts res = tree.reverse_each { |v, k| puts v }

GC.start

h = {_1: :_2, _3: :_4}
puts h.each_key.next

puts "exit 0"

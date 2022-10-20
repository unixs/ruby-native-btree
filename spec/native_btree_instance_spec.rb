# frozen_string_literal: true

RSpec.describe NativeBtree do

  describe NativeBtree::Btree do
    let(:tree) do
      described_class.new do |a, b|
        a - b
      end
    end

    describe "#[]= method" do

      it "respond to" do
        expect(tree).to respond_to('[]=')
      end

      it 'set key/value pair' do
        tree[2] = 22
        expect(tree[2]).to be 22
      end

      it "pass key arg and value" do
        expect(tree[:key] = 10).to be 10
      end

      it "Raise ArgumentError if key was not passed" do
        expect { tree[] = 1 }.to raise_error(ArgumentError)
      end

      it 'Call comparator while set value' do
        comparator = spy('comparator')
        def comparator.to_proc
          proc do |a, b|
            comparator.call()
            a - b
          end
        end

        btree = described_class.new(&comparator)
        btree[1] = 1
        btree[2] = 2
        expect(comparator).to have_received(:call)
      end

      it 'has a set alias' do
        expect(tree).to respond_to('set')
      end
    end

    describe "#[] method" do
      it "respond to" do
        expect(tree).to respond_to('[]')
      end

      it 'return expected value if found' do
        tree[3] = 'a'
        tree[4] = 'b'
        expect(tree[3]).to be 'a'
      end

      it 'return nil if not found' do
        tree[1] = '1'
        tree[5] = '5'
        expect(tree[2]).to be_nil
      end

      it 'has a get alias' do
        expect(tree).to respond_to('get')
      end
    end

    describe "#height method" do
      it "respond to" do
        expect(tree).to respond_to(:height)
      end

      it 'return tree height with items' do
        tree[1] = 11
        tree[2] = 22
        tree[3] = 33
        tree[4] = 44
        expect(tree.height).to be 3
      end

      it 'return 0 if empty tree' do
        expect(tree.height).to be 0
      end
    end

    describe "#size method" do
      it "respond to" do
        expect(tree).to respond_to(:size)
      end

      it 'return count of nodes' do
        tree[1] = 1
        tree[2] = 2
        tree[3] = 3
        expect(tree.size).to be 3
      end

      it 'return 0 if empty tree' do
        expect(tree.size).to be 0
      end

    end

    describe "#delete method" do
      it "respond to" do
        expect(tree).to respond_to(:delete)
      end

      it 'delete key value pair' do
        tree[2] = 22
        tree[3] = 33
        tree.delete(3)
        expect(tree[3]).to be_nil
      end

      it "return nil if not found" do
        tree[3] = 33
        expect(tree.delete(4)).to be_nil
      end

      it "return value if key is found" do
        tree[2] = 22
        tree[3] = 33
        expect(tree.delete(2)).to be 22
      end

      it "call block with key if not found" do
        tree[2] = 22
        block = ->(key) { "#{key} is not found" }
        expect(tree.delete(7, &block)).to be == "7 is not found"
      end
    end

    describe "#clear method" do
      it "respond to" do
        expect(tree).to respond_to(:clear)
      end

      it 'clear tree' do
        tree[1] = 11
        tree[2] = 22
        tree[3] = 33
        expect(tree.size).to be 3
        tree.clear()
        expect(tree.size).to be 0
      end

      it 'return self' do
        tree[1] = 11
        expect(tree.clear()).to be tree
      end
    end

    describe "#include? method" do
      it "respond to" do
        expect(tree).to respond_to(:include?)
      end

      it 'return true is key exists' do
        tree[3] = 33
        expect(tree.include?(3)).to be true
      end

      it 'return false if key not exists' do
        tree[3] = 33
        expect(tree.include?(4)).to be false
      end
    end

    describe "#empty? method" do
      it 'respond to' do
        expect(tree).to respond_to(:empty?)
      end

      it 'return false if nodes exists' do
        tree[3] = 33
        expect(tree.empty?).to be false
      end

      it 'return true if nodes not exists' do
        expect(tree.empty?).to be true
      end
    end

    describe '#== method' do
      let(:tree2) do
        described_class.new do |a, b|
          a - b
        end
      end

      it 'respond to' do
        expect(tree).to respond_to(:==)
      end

      it 'return true if eql' do
        tree[1] = 11
        tree[2] = 22
        tree[7] = 77

        tree2[7] = 77
        tree2[2] = 22
        tree2[1] = 11

        expect(tree).to eq tree2
      end

      it 'return false if not eql' do
        tree[1] = 11
        tree[2] = 22
        tree[7] = 77
        tree[8] = 88

        tree2[7] = 77
        tree2[2] = 22
        tree2[1] = 11

        expect(tree).not_to eq tree2
      end

      it 'return true if are empty trees' do
        expect(tree).to eq tree2
      end

      it 'return false if one key is not eq' do
        tree[5] = 11
        tree[2] = 22
        tree[7] = 77

        tree2[7] = 77
        tree2[2] = 22
        tree2[1] = 11

        expect(tree).not_to eq tree2
      end

      it 'return false if one value is not eq' do
        tree[1] = 11
        tree[2] = 22
        tree[7] = 7

        tree2[7] = 77
        tree2[2] = 22
        tree2[1] = 11

        expect(tree).not_to eq tree2
      end

      it 'return false if any tree is empty' do
        tree[1] = 11
        tree[2] = 22

        expect(tree).not_to eq tree2
      end
    end

    describe '#last method' do
      it 'respond to' do
        expect(tree).to respond_to(:last)
      end

      it 'return correct value' do
        tree[1] = 10
        tree[10] = 20
        tree[20] = 30

        expect(tree.last).to eq(30)
      end

      it 'return nil if empty' do
        expect(tree.last).to be_nil
      end
    end

    describe '#first method' do
      it 'respond to' do
        expect(tree).to respond_to(:first)
      end

      it 'return correct value' do
        tree[1] = 10
        tree[10] = 20
        tree[20] = 30

        expect(tree.first).to eq(10)
      end

      it 'return nil if empty' do
        expect(tree.first).to be_nil
      end
    end

    describe '#delete_if method' do
      it 'respond to' do
        expect(tree).to respond_to(:delete_if)
      end

      it 'return self if empty' do
        expect(tree.delete_if { |_, _| false }).to be_nil
      end
    end

  end
end

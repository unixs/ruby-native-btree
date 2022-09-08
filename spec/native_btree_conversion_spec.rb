# frozen_string_literal: true

RSpec.describe NativeBtree do

  describe NativeBtree::Btree do
    let(:tree) do
      described_class.new do |a, b|
        a - b
      end
    end

    describe "to_ methods" do
      describe "#to_a" do
        it "respond to" do
          expect(tree).to respond_to(:to_a)
        end

        it 'return Array' do
          expect(tree.to_a).to be_kind_of(Array)
        end

        it 'has similar items' do
          tree[2] = 22
          tree[1] = 11
          expect(tree.to_a()[0][1]).to be 11
        end
      end

      describe "#to_h" do
        it "respond to" do
          expect(tree).to respond_to(:to_h)
        end

        it "return Hash" do
          expect(tree.to_h).to be_kind_of(Hash)
        end

        it 'has similar keys' do
          tree[2] = 22
          tree[1] = 11
          expect(tree.to_h()[1]).to be 11
        end
      end
    end
  end
end

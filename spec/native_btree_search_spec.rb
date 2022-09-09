# frozen_string_literal: true

RSpec.describe NativeBtree do

  describe NativeBtree::Btree do
    let(:tree) do
      described_class.new do |a, b|
        a - b
      end
    end

    describe "#filter method" do
      it "respond to" do
        expect(tree).to respond_to(:filter)
      end

      it 'raise error if block not given' do
        expect { tree.filter() }.to raise_error(LocalJumpError)
      end

      it 'return Btree instance' do
        expect(tree.filter() { nil }).to be_kind_of(described_class)
      end

      it 'filter tree by values' do
        tree[1] = 11
        tree[5] = 90
        tree[2] = 32
        tree[100] = 15
        tree[46] = 8

        expect(tree.filter { |v| v > 20 }.to_a).to match_array([[2, 32], [5, 90]])
      end

      it 'filter tree by keys' do
        tree[1] = 11
        tree[5] = 90
        tree[2] = 32
        tree[100] = 15
        tree[46] = 8

        expect(tree.filter { |_v, k| k > 20 }.to_a).to match_array([[46, 8], [100, 15]])
      end
    end

    describe "#filter! method" do
      xit "respond to" do
        expect(described_cless.respond_to?(:filter!)).to be true
      end
    end

    describe "#select method" do
      xit "respond to" do
        expect(described_cless.respond_to?(:select)).to be true
      end
    end

    describe "#select! method" do
      xit "respond to" do
        expect(described_cless.respond_to?(:select!)).to be true
      end
    end
  end
end

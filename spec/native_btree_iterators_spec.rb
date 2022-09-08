# frozen_string_literal: true

RSpec.describe NativeBtree do

  describe NativeBtree::Btree do
    let(:tree) do
      described_class.new do |a, b|
        a - b
      end
    end

    describe "#each method" do
      it "respond to" do
        expect(tree).to respond_to(:each)
      end

      it 'yield in to block value first' do
        tree[2] = 22

        value = nil
        tree.each { |v| value = v }

        expect(value).to be 22
      end

      it 'yield in to block key second' do
        tree[2] = 22

        key = nil
        tree.each { |_v, k| key = k }

        expect(key).to be 2
      end

      it 'yield ordered keys' do
        tree[16] = 16
        tree[0] = 0
        tree[5] = 5
        tree[-4] = -4
        tree[7] = 7

        check = [-4, 0, 5, 7, 16]
        result = []
        tree.each { |value| result << value }

        expect(result).to eq(check)
      end
    end

    describe "#each_key method" do
      xit "respond to" do
        expect(described_cless.respond_to?(:each_key)).to be true
      end
    end

    describe "#each_value method" do
      xit "respond to" do
        expect(described_cless.respond_to?(:each_value)).to be true
      end
    end
  end
end

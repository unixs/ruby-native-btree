# frozen_string_literal: true

RSpec.describe NativeBtree do
  it "has a version number" do
    expect(NativeBtree::VERSION).not_to be_nil
  end

  describe NativeBtree::Btree do

    describe "initialize class method" do
      it 'respond to new' do
        expect(described_class).to respond_to('new').with(0).arguments
      end

      it "return new btree instance" do
        expect(described_class.new { nil }).to be_kind_of(described_class)
      end

      it "raise error if block is not given" do
        expect { described_class.new() }.to raise_error(LocalJumpError)
      end

      it 'return new btree with int comparator' do
        expect(described_class.new(described_class::INT_COMPARATOR))
          .to be_kind_of(described_class)
      end

    end

    describe "constants" do
      it 'has const INT_COMPARATOR' do
        expect(described_class.const_defined?(:INT_COMPARATOR)).to be true
      end

      it 'const INT_COMPARATOR is 1' do
        expect(described_class::INT_COMPARATOR).to be 128
      end
    end
  end
end

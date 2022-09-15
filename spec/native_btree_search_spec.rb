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

      it 'return new object' do
        tree[1] = 11
        tree[5] = 90
        tree[2] = 32
        tree[100] = 15
        tree[46] = 8

        result = tree.filter { |_v, k| k > 20 }

        expect(tree.equal?(result)).to be false
      end

      it 'construct correct tree with int comparator' do
        tree = described_class.new(described_class::INT_COMPARATOR)

        tree[1] = 11
        tree[5] = 90
        tree[2] = 32
        tree[100] = 15
        tree[46] = 8

        expect(tree.filter { |v| v > 20 }.to_a).to match_array([[2, 32], [5, 90]])
      end
    end

    describe "#filter! method" do
      it "respond to" do
        expect(tree).to respond_to(:filter!)
      end

      it 'raise error if block not given' do
        expect { tree.filter!() }.to raise_error(LocalJumpError)
      end

      it 'return Btree instance' do
        expect(tree.filter!() { nil }).to be_kind_of(described_class)
      end

      it 'return origin tree' do
        tree[1] = 11
        tree[5] = 90
        tree[2] = 32
        tree[100] = 15
        tree[46] = 8

        result = tree.filter! { |_v, k| k > 20 }

        expect(tree.equal?(result)).to be true
      end

      it 'filter tree by values' do
        tree[1] = 11
        tree[5] = 90
        tree[2] = 32
        tree[100] = 15
        tree[46] = 8

        expect(tree.filter! { |v| v > 20 }.to_a)
          .to match_array([[2, 32], [5, 90]])
      end

      it 'filter tree by keys' do
        tree[1] = 11
        tree[5] = 90
        tree[2] = 32
        tree[100] = 15
        tree[46] = 8

        expect(tree.filter! { |_v, k| k > 20 }.to_a)
          .to match_array([[46, 8], [100, 15]])
      end

    end

    describe "#select method" do
      it "respond to" do
        expect(tree).to respond_to(:select)
      end
    end

    describe "#select! method" do
      it "respond to" do
        expect(tree).to respond_to(:select!)
      end
    end

    if NativeBtree::Glib::MAJOR_VERSION == 2 &&
       NativeBtree::Glib::MINOR_VERSION >= 68

      describe "select_before method" do
        it 'respond_to' do
          expect(tree).to respond_to(:select_before)
        end

        it 'return expected collection' do
          tree[1] = 11
          tree[2] = 32
          tree[5] = 90
          tree[46] = 8
          tree[100] = 15

          expect(tree.select_before(5).to_a)
            .to match_array([[1, 11], [2, 32], [5, 90]])
        end

        it 'return correct tree if one target' do
          tree[100] = 15
          tree[46] = 8
          tree[5] = 90

          expect(tree.select_before(5).to_a)
            .to match_array([[5, 90]])
        end

        it 'return empty tree if no targets' do
          tree[100] = 15
          tree[46] = 8

          expect(tree.select_before(5).to_a)
            .to match_array([])
        end
      end

      describe "select_after" do
        it "respond to" do
          expect(tree).to respond_to(:select_after)
        end

        it 'return expected collection' do
          tree[1] = 11
          tree[5] = 90
          tree[2] = 32
          tree[100] = 15
          tree[46] = 8

          expect(tree.select_after(5).to_a)
            .to match_array([[5, 90], [46, 8], [100, 15]])
        end

        it 'return correct tree if one target' do
          tree[3] = 15
          tree[4] = 8
          tree[5] = 90

          expect(tree.select_after(5).to_a)
            .to match_array([[5, 90]])
        end

        it 'return empty tree if no targets' do
          tree[1] = 11
          tree[2] = 32

          expect(tree.select_after(5).to_a)
            .to match_array([])
        end
      end

      describe "select_between" do
        xit "respond to" do
          expect(tree).to respond_to(:select_between)
        end
      end

    end
  end
end

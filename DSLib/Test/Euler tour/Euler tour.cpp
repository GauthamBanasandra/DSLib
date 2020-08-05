#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Eulertour
{
	TEST_CLASS(Eulertour)
	{
	public:

		TEST_METHOD(TestCircuit1)
		{
			const std::vector<std::pair<EulerTour::NodeId, EulerTour::NodeId>> edge_list{
				/*{0, 1},
				{0, 2},
				{1, 2},
				{1, 4},
				{1, 3},
				{2, 4},
				{2, 3},
				{4, 3}*/

				{0, 4},
				{4, 1},
				{1, 2},
				{2, 4},
				{4, 3},
				{3, 0}
			};

			const size_t num_nodes = 5;

			for (EulerTour::NodeId node_id = 0; node_id < num_nodes; ++node_id)
			{
				EulerTour tour(num_nodes, edge_list, false);
				Assert::IsTrue(ValidateCircuit(tour.Get(node_id)));
			}
		}

	private:
		[[nodiscard]] bool ValidateCircuit(const std::list<EulerTour::Edge>& tour) const
		{
			if (tour.size() < 2)
			{
				return false;
			}

			auto it = tour.begin();
			auto previous{ *it };
			auto current{ *++it };
			for (; it != tour.end(); ++it)
			{
				current = *it;
				if (current.first != previous.second)
				{
					return false;
				}
				std::swap(current, previous);
			}

			return tour.front().first == tour.back().second;
		}
	};
}

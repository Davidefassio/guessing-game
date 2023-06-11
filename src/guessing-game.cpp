#include "gg-strategy.hpp"

#include <chrono>

int main()
{
    int maxn = 9;
    Mat64f res = Mat64f::zeros(maxn, maxn);

    auto start = std::chrono::system_clock::now();

    for (int i = 1; i < maxn; ++i)
    {
        std::vector<std::uint8_t> occ(i);
        for (int j = 1; j <= i; ++j)
        {
            auto perms = Utils::create_disposition(i, j);
            std::uint64_t tot = 0;

            for (std::uint64_t c = 0; c < perms.rows(); ++c)
            {
                std::vector<std::uint64_t> disp(perms.rows());
                std::iota(disp.begin(), disp.end(), 0);

                std::uint64_t guesses = 0;

                while (true)
                {
                    ++guesses;

                    auto sp = get_results(perms, i, disp[0], c);

                    if (sp.p == perms.cols())
                        break;

                    std::vector<std::uint64_t> ndisp;
                    for (std::uint64_t d = 1; d < disp.size(); ++d)
                        if (verify_legality(perms, occ, disp[d], disp[0], sp))
                            ndisp.push_back(disp[d]);
                    
                    disp = ndisp;
                }

                tot += guesses;
            }

            res.set(i, j, tot / static_cast<double>(perms.rows()));
            std::cout << i << " " << j << ": " << res.get(i, j) << std::endl;
        }
    }

    auto end = std::chrono::system_clock::now();
    std::cout << "Calculations: " << std::chrono::duration_cast<std::chrono::seconds>(end - start) << std::endl;

    res.debug();

    return 0;
}

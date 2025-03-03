#ifndef DIFF_HPP
#define DIFF_HPP

#include <vector>


class DiffMethod {
    public:
        virtual ~DiffMethod() = default;
        virtual std::vector<double> compute(
            const std::vector<double>& f, const std::vector<double>& x
        ) const = 0;
};


class SecondOrderCenterDiff : public DiffMethod {
    public:
        std::vector<double> compute(
            const std::vector<double>& f, const std::vector<double>& x
        ) const override;
};




#endif //DIFF_HPP
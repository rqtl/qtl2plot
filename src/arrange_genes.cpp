// arrange_genes, helper function for plot_genes
//
// take vectors (start, stop) and return y values in {1, 2, ...}
// so that the genes won't overlap

#include "arrange_genes.h"
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
IntegerVector arrange_genes(const NumericVector& start,
                            const NumericVector& end)
{
    const unsigned int n = start.size();
    IntegerVector result(n);

    // check inputs
    if(end.size() != n) {
        throw std::invalid_argument("Must have length(start) == length(end)");
    }
    if(n==1) {
        result[0] = 1;
        return(result);
    } else if(n < 1) {
        throw std::invalid_argument("Must have length(start) >= 1");
    }

    int maxy = result[0] = 1;
    std::vector<int> maxx;
    maxx.push_back(end[0]);

    for(unsigned int i=1; i<n; i++) {
        for(unsigned int j=0; j<maxy; j++) {
            if(start[i] > maxx[j]) {
                result[i] = j+1;
                maxx[j] = end[i];
                break;
            }
        }

        if(result[i] == 0) {
            result[i] = maxy + 1;
            maxy++;
            maxx.push_back(end[i]);
        }
    }

    return(result);
}
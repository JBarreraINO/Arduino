rm the distribution's CDF to get a linear relationship between
% some function of the data and some function of the cumulative
% probability.  These two functions do not involve the distribution
% parameters, but the slope and intercept of the line do.
% * Plug the values of x and p from the ECDF into that transformed CDF, and
% fit a straight line using least squares.
% * Solve for the distribution parameters in terms of the slope and
% intercept of the line.
%
% We also saw that fitting a distribution that is a location-scale family
% with an additional a threshold parameter is only slightly more difficult.
%
% But other distributions that are not location-scale families, like the
% gamma, are a bit trickier.  There's no transformation of the CDF that
% will give a relationship that is linear.  However, we can use a similar
% idea, only this time working on the untransformed cumulative probability
% scale.  A P-P plot is the appropriate way to visualize that fitting
% procedure.
%
% If the empirical probabilities from the ECDF are plotted against fitted
% probabilities from a parametric model, a tight scatter along the 1:1 line
% from zero to one indicates that the parameter values define a
% distribution that explains the observed data well, because the fitted CDF
% approximates the empirical CDF well.  The idea is to find parameter
% values that make the probability plot as close to the 1:1 line as
% possible.  That may not even be possible, if the distribution is not a
% good model for the data.  If the P-P plot shows a systematic departure
% from the 1:1 line, then the model may be questionable.  However, it's
% important to remember that since the points in these plots are not
% independent, interpretation is not exactly the same as a regression
% residual plot.
%
% For example, we'll simulate some data and fit a gamma distribution.
n = 100;
x = gamrnd(2,1,n,1);

%%
% Compute the ECDF of x.
x = sort(x);
pEmp = ((1:n)-0.5)' ./ n;

%%
% We can make a probability plot using any initial guess for the gamma
% distribution's parameters, a=1 and b=1, say.  That guess is not very good REPLACE_WITH_DASH_DASH
% the probabilities from the parametric CDF are not close to the probabilities
% from the ECDF.  If we tried a different a and b, we'd get a different
% scatter on the P-P plot, with a different discrepancy from the 1:1 line.
% Since we know the true a and b in this example, we'll try those values.
a0 = 1; b0 = 1;
p0Fit = gamcdf(x,a0,b0);
a1 = 2; b1 = 1;
p1Fit = gamcdf(x,a1,b1);
plot([0 1],[0 1],'kREPLACE_WITH_DASH_DASH', pEmp,p0Fit,'b+', pEmp,p1Fit,'r+');
xlabel('Empirical Probabilities');
ylabel('(Provisionally) Fitted Gamma Probabilities');
legend({'1:1 Line
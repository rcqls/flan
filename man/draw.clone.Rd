\name{draw.clone}
\alias{draw.clone}
\encoding{UTF-8}


\title{Graphic representation of clone growing upon a finite time.}

\description{
  Simulates a clone up to a time t and represents the clone as a binary tree.
}

\usage{
  draw.clone(t,mutprob=1e-2,fitness=1,death=0,
	     dist=list("lnorm",meanlog=-0.3795851,sdlog=0.3016223))
}

\arguments{
  \item{t}{ time of end of experiment . } 
  \item{mutprob}{ mutation probability: numeric between 0 and 1. By default 1e-2. }
  \item{fitness}{ fitness parameter: numeric positive. }
  \item{death}{ death probability: numeric between 0 and 0.5. } 
  \item{dist}{ lifetime distribution for mutant cells. See Details. }
}


\details{
  
  This function does not provide a representation of a realistic realization of a mutation model (mutation probability too high, time of end of experiment to small).
  
  The argument \code{dist} is a list beginning with the distribution name followed by its parameters, and must be one the 4 following distributions: "dirac"(location), "exp"(rate), "lnorm"(meanlog, sdlog), "gamma"(shape, scale). 
  
  
  
}

\seealso{
  \code{\link{rflan}}
}

\examples{


# Luria-Delbrück model, mutation probability 1e-2, fitness 1
draw.clone(t=9,dist=list(name="exp",rate=1))

# Luria-Delbrück model, mutation probability 0.1, fitness 0.6
draw.clone(t=9,mutprob=0.1,fitness=0.6,dist=list(name="exp",rate=1))

# Haldane model, mutation probability 1e-2, fitness 1
draw.clone(t=7,dist=list(name="dirac",location=1))

# Lognormal lifetime distribution 
draw.clone(t=7,fitness=0.5,death=0.1)

# Luria-Delbrück model with positive cell death probability
draw.clone(t=7,dist=list(name="exp",rate=1),death=0.2)

}


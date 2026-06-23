const filter1 = (list: (number | undefined)[]): number[] => list.filter(x => x !== undefined);

const filter2 = (list: (number | undefined)[]): number[] => list.filter(x => x !== undefined && x > 5);
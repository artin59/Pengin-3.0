export const useLocalStorage = (key : string) => {

    const setItem = (value : unknown) => {

        try {
            window.localStorage.setItem(key, JSON.stringify(value));
        } 
        
        catch (error) {
            console.log(error);
        }
        
    };
    return {setItem};
}
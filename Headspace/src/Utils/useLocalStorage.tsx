export const useLocalStorage = (key : string) => {

    const setItem = (value : unknown) => {

        try {
            window.localStorage.setItem(key, JSON.stringify(value));
        } 
        
        catch (error) {
            console.log(error);
        }
        
    };

    const getItem = () => {
        try {
            const item = window.localStorage.getItem(key);
            if (item)
                return JSON.parse(item);
            else    
                return undefined
        } 
        catch (error){
            console.log(error);
        }
    };

    return {setItem, getItem};
}